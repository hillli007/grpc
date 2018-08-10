/*
 * Author: lixiaolong
 */

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "demo/protos/demo.grpc.pb.h"
#else
#include "demo.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using demo::DemoRequest;
using demo::DemoReply;
using demo::Greeter;

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel) :
            stub_(Greeter::NewStub(channel)) {
    }

    std::string SignIn(const std::string& user, const std::string& pwd) {
        DemoRequest request;
        request.set_username(user);
        request.set_pwd(pwd);

        DemoReply reply;
        ClientContext context;
        Status status = stub_->SignIn(&context, request, &reply);

        if (status.ok()) {
            return reply.message();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
            return "RPC failed";
        }
    }

private:
    std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
    bool signin_on = false;
    bool signup_on = false;
    bool username_on = false;
    bool password_on = false;

    char *user_name;
    char *password;

    for (int i = 1; i < argc; ++i) {
        //std::cout << "argv[" << i << "]:" << argv[i] << std::endl;
        char *pchar = argv[i];
        switch (pchar[0]) {
        case '-': {
            //std::cout << "case \'-\' found" << std::endl;
            switch (pchar[1]) {
            case 'l':
                signin_on = true;
            case 'r':
                signup_on = true;
            case 'u':
                username_on = true;
                break;
            case 'p':
                password_on = true;
                break;
            default:
                std::cout << "Invalid param:  " << pchar[1] << std::endl;
            }
            break;
        }
        default:
            if (username_on) {
                //std::cout << "user name: " << pchar << std::endl;
                user_name = pchar;
                username_on = false;
            } else if (password_on) {
                //std::cout << "password: " << pchar << std::endl;
                password = pchar;
                password_on = false;
            }
            break;
        }
    }

    GreeterClient greeter(
            grpc::CreateChannel("localhost:50051",
                    grpc::InsecureChannelCredentials()));
    if (signin_on) {
        std::string user(user_name);
        std::string pwd(password);
        std::string reply = greeter.SignIn(user, pwd);
        std::cout << "Sign In: " << reply << std::endl;
    } else if (signup_on) {

    }
    return 0;
}
