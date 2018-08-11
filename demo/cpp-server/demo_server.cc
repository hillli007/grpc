/*
 * Author: lixiaolong
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>

#ifdef BAZEL_BUILD
#include "demo/protos/demo.grpc.pb.h"
#else
#include "demo.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using demo::DemoRequest;
using demo::DemoReply;
using demo::Greeter;

using namespace std;
using namespace sql;

class GreeterServiceImpl final : public Greeter::Service {
public:
    Driver *driver;
    Connection *con;

    GreeterServiceImpl() {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "123456");
    }

    ~GreeterServiceImpl() {
        delete con;
    }

    Status SignIn(ServerContext* context, const DemoRequest* request, DemoReply* reply) override {
        cout << request->username() << " call SignIn " << request->pwd() << endl;

        Statement* state = con->createStatement();
        state->execute("use demo_db");

        string sql = "select * from users where user_name='";
        sql += request->username();
        sql += "' and pwd='";
        sql += request->pwd();
        sql += "';";
        cout << sql << endl;
        ResultSet* result = state->executeQuery(sql);

        bool valid = false;
        while (result->next()) {
            try {
                string user = result->getString("user_name");
                valid = true;
            } catch (sql::SQLException& e) {
                cout << e.what() << endl;
            }
        }

        if(valid) {
            reply->set_message("success");
        } else {
            reply->set_message("failed");
        }

        return Status::OK;
    }

    Status SignUP(ServerContext* context, const DemoRequest* request, DemoReply* reply) override {
        cout << request->username() << " call Sign Up " << request->pwd() << endl;
        Statement* state = con->createStatement();
        state->execute("use demo_db");
        string sql = "INSERT INTO users (user_name, pwd, online) VALUES ('";
        sql += request->username();
        sql += "', '";
        sql += request->pwd();
        sql += "', 'false');";
        cout << sql << endl;
        int res = state->executeUpdate(sql);
        if(res == 1) {
            reply->set_message("success");
        } else {
            reply->set_message("failed");
        }
        return Status::OK;
    }

};

void RunServer() {
    string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    unique_ptr<Server> server(builder.BuildAndStart());
    cout << "Server listening on " << server_address << endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
