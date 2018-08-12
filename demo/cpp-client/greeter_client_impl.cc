#include "../cpp-client/greeter_client_impl.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "greeter_client.hpp"
#include "demo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using demo::DemoRequest;
using demo::DemoReply;
using demo::Greeter;

std::string grpcdemo::GreeterClientImpl::SignIn(const std::string& platform, const std::string& name,
        const std::string& pwd) {
    DemoRequest request;
    request.set_platform(platform);
    request.set_username(name);
    request.set_pwd(pwd);

    DemoReply reply;
    ClientContext context;
    Status status = stub_->SignIn(&context, request, &reply);

    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string grpcdemo::GreeterClientImpl::LogOut(const std::string& platform, const std::string& name,
        const std::string& pwd) {
    DemoRequest request;
    request.set_platform(platform);
    request.set_username(name);
    request.set_pwd(pwd);

    DemoReply reply;
    ClientContext context;
    Status status = stub_->LogOut(&context, request, &reply);

    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string grpcdemo::GreeterClientImpl::HeartBeat(const std::string& platform, const std::string& name,
        const std::string& pwd) {
    DemoRequest request;
    request.set_platform(platform);
    request.set_username(name);
    request.set_pwd(pwd);

    DemoReply reply;
    ClientContext context;
    Status status = stub_->HeartBeat(&context, request, &reply);

    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

std::string grpcdemo::GreeterClientImpl::SignUp(const std::string& name, const std::string& pwd) {
    DemoRequest request;
    request.set_username(name);
    request.set_pwd(pwd);

    DemoReply reply;
    ClientContext context;
    Status status = stub_->SignUp(&context, request, &reply);

    if (status.ok()) {
        return reply.message();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return "RPC failed";
    }
}

grpcdemo::GreeterClientImpl::GreeterClientImpl(const std::string & host_port) {
    std::shared_ptr<Channel> channel = grpc::CreateChannel(host_port, grpc::InsecureChannelCredentials());
    stub_ = Greeter::NewStub(channel);
}

grpcdemo::GreeterClientImpl::~GreeterClientImpl() {
}

