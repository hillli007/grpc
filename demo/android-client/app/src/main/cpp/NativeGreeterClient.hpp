// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from greeter.djinni

#pragma once

#include "djinni_support.hpp"
#include "greeter_client.hpp"

namespace djinni_generated {

class NativeGreeterClient final : ::djinni::JniInterface<::grpcdemo::GreeterClient, NativeGreeterClient> {
public:
    using CppType = std::shared_ptr<::grpcdemo::GreeterClient>;
    using CppOptType = std::shared_ptr<::grpcdemo::GreeterClient>;
    using JniType = jobject;

    using Boxed = NativeGreeterClient;

    ~NativeGreeterClient();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeGreeterClient>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeGreeterClient>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeGreeterClient();
    friend ::djinni::JniClass<NativeGreeterClient>;
    friend ::djinni::JniInterface<::grpcdemo::GreeterClient, NativeGreeterClient>;

};

}  // namespace djinni_generated
