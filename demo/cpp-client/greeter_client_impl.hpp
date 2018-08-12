#ifndef greeter_client_impl_hpp
#define greeter_client_impl_hpp

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "greeter_client.hpp"
#include "demo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using demo::DemoRequest;
using demo::DemoReply;
using demo::Greeter;

namespace grpcdemo {

    class GreeterClientImpl: public GreeterClient {

        public:
            GreeterClientImpl(const std::string & host_port);
            ~GreeterClientImpl();
            std::string LogOut(const std::string & platform, const std::string & name, const std::string & pwd);
            std::string SignIn(const std::string & platform, const std::string & name, const std::string & pwd);
            std::string SignUp(const std::string & name, const std::string & pwd);
            std::string HeartBeat(const std::string & platform, const std::string & name, const std::string & pwd);

        private:
            std::unique_ptr<Greeter::Stub> stub_;
    };

}
#endif
