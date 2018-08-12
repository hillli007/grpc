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
        return InnerSignIn(context, request, reply, true, false);
    }

    Status LogOut(ServerContext* context, const DemoRequest* request, DemoReply* reply) override {
        cout << request->username() << " call LogOut " << request->pwd() << endl;
        return InnerSignIn(context, request, reply, false, false);
    }

    Status HeartBeat(ServerContext* context, const DemoRequest* request, DemoReply* reply) override {
        cout << request->username() << " call LogOut " << request->pwd() << endl;
        return InnerSignIn(context, request, reply, false, true);
    }

    Status InnerSignIn(ServerContext* context, const DemoRequest* request, DemoReply* reply, bool isIn,
            bool heartbeat) {

        Statement* state = con->createStatement();
        state->execute("use demo_db");

        // 查询合法用户
        string sql = "select * from users where user_name='";
        sql += request->username();
        sql += "' and pwd='";
        sql += request->pwd();
        sql += "';";
        cout << sql << endl;
        ResultSet* result = state->executeQuery(sql);

        bool valid = false;
        string id,curOnlineDevice;
        while (result->next()) {
            try {
                valid = true;
                id = result->getString("id_users");
                curOnlineDevice = result->getString("online");
            } catch (sql::SQLException& e) {
                cout << e.what() << endl;
            }
        }

        if (valid) {
            if(heartbeat) {
                cout << "heartbeat -->" << curOnlineDevice << endl;
                reply->set_message("heartbeat:" + curOnlineDevice);
            } else {
                string platform = request->platform();
                // 改变登录状态
                string sql = "UPDATE users SET online='";
                sql += isIn ? platform : "offline";
                sql += "' WHERE id_users='";
                sql += id;
                sql += "';";
                cout << sql << endl;
                int res = state->executeUpdate(sql);
                if (res == 1) {
                    reply->set_message("success:" + (isIn ? platform : "logout"));
                } else {
                    reply->set_message("success:nochange");
                }
            }
        } else {
            reply->set_message("failed:nouser");
        }

        return Status::OK;
    }

    Status SignUp(ServerContext* context, const DemoRequest* request, DemoReply* reply) override {
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
        if (res == 1) {
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
