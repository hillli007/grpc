#include <atomic>

#include <grpc++/grpc++.h>
#include <jni.h>

#include "demo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using demo::Greeter;
using demo::DemoReply;
using demo::DemoRequest;

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


extern "C"
JNIEXPORT jstring JNICALL
Java_com_lxl_demo_gprc_DemoActivity_signin(JNIEnv *env, jclass type, jstring host_, jint port,
                                           jstring username_, jstring pwd_) {
    const char *host = env->GetStringUTFChars(host_, 0);
    const char *username = env->GetStringUTFChars(username_, 0);
    const char *pwd = env->GetStringUTFChars(pwd_, 0);

    const char* host_chars = env->GetStringUTFChars(host_raw, (jboolean*)0);
    std::string host(host_chars, env->GetStringUTFLength(host_raw));

    int port = static_cast<int>(port_raw);

    const char* message_chars = env->GetStringUTFChars(message_raw, (jboolean*)0);
    std::string message(message_chars, env->GetStringUTFLength(message_raw));

    const int host_port_buf_size = 1024;
    char host_port[host_port_buf_size];
    snprintf(host_port, host_port_buf_size, "%s:%d", host.c_str(), port);

    GreeterClient greeter(grpc::CreateChannel(host_port, grpc::InsecureChannelCredentials()));
    std::string reply = greeter.SignIn(message,message);
    return env->NewStringUTF(reply.c_str());
}