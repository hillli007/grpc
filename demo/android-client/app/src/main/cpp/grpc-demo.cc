#include <atomic>

#include <grpc++/grpc++.h>
#include <jni.h>

#include "demo.grpc.pb.h"

#include <grpcpp/grpcpp.h>
#include "greeter_client_impl.hpp"

using namespace grpcdemo;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lxl_demo_gprc_DemoActivity_signin(JNIEnv *env, jclass type, jstring host_, jint port_, jstring username_, jstring pwd_) {

    const char *host_chars = env->GetStringUTFChars(host_, 0);
    const char *username_chars = env->GetStringUTFChars(username_, 0);
    const char *pwd_chars = env->GetStringUTFChars(pwd_, 0);

    std::string host(host_chars, env->GetStringUTFLength(host_));
    std::string username(username_chars, env->GetStringUTFLength(username_));
    std::string pwd(pwd_chars, env->GetStringUTFLength(pwd_));

    int port = static_cast<int>(port_);
    const int host_port_buf_size = 1024;
    char host_port[host_port_buf_size];
    snprintf(host_port, host_port_buf_size, "%s:%d", host.c_str(), port);

    GreeterClientImpl greeter(host_port);
    std::string reply = greeter.SignIn(username,pwd);

    env->ReleaseStringUTFChars(host_, host_chars);
    env->ReleaseStringUTFChars(username_, username_chars);
    env->ReleaseStringUTFChars(pwd_, pwd_chars);
    return env->NewStringUTF(reply.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_lxl_demo_gprc_DemoActivity_signup(JNIEnv *env, jclass type, jstring host_, jint port_, jstring username_, jstring pwd_) {
    const char *host_chars = env->GetStringUTFChars(host_, 0);
    const char *username_chars = env->GetStringUTFChars(username_, 0);
    const char *pwd_chars = env->GetStringUTFChars(pwd_, 0);

    std::string host(host_chars, env->GetStringUTFLength(host_));
    std::string username(username_chars, env->GetStringUTFLength(username_));
    std::string pwd(pwd_chars, env->GetStringUTFLength(pwd_));

    int port = static_cast<int>(port_);
    const int host_port_buf_size = 1024;
    char host_port[host_port_buf_size];
    snprintf(host_port, host_port_buf_size, "%s:%d", host.c_str(), port);

    GreeterClientImpl greeter(host_port);
    std::string reply = greeter.SignUp(username,pwd);

    env->ReleaseStringUTFChars(host_, host_chars);
    env->ReleaseStringUTFChars(username_, username_chars);
    env->ReleaseStringUTFChars(pwd_, pwd_chars);
    return env->NewStringUTF(reply.c_str());
}