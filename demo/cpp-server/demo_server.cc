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

class GreeterServiceImpl final : public Greeter::Service {

    Status SignIn(ServerContext* context, const DemoRequest* request, DemoReply* reply) override {
        std::string prefix("Sign In: ");
        reply->set_message(prefix + request->username());
        return Status::OK;
    }

    Status SignUP(ServerContext* context, const DemoRequest* request, DemoReply* reply) override {
        std::string prefix("Sign Up: ");
        reply->set_message(prefix + request->username());
        return Status::OK;
    }

};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
