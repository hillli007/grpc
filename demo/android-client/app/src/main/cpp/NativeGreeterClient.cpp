// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from greeter.djinni

#include "NativeGreeterClient.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

NativeGreeterClient::NativeGreeterClient() : ::djinni::JniInterface<::grpcdemo::GreeterClient, NativeGreeterClient>("com/lxl/demo/gprc/GreeterClient$CppProxy") {}

NativeGreeterClient::~NativeGreeterClient() = default;


CJNIEXPORT void JNICALL Java_com_lxl_demo_gprc_GreeterClient_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::grpcdemo::GreeterClient>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jstring JNICALL Java_com_lxl_demo_gprc_GreeterClient_00024CppProxy_native_1HeartBeat(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_platform, jstring j_name, jstring j_pwd)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::grpcdemo::GreeterClient>(nativeRef);
        auto r = ref->HeartBeat(::djinni::String::toCpp(jniEnv, j_platform),
                                ::djinni::String::toCpp(jniEnv, j_name),
                                ::djinni::String::toCpp(jniEnv, j_pwd));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_com_lxl_demo_gprc_GreeterClient_00024CppProxy_native_1LogOut(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_platform, jstring j_name, jstring j_pwd)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::grpcdemo::GreeterClient>(nativeRef);
        auto r = ref->LogOut(::djinni::String::toCpp(jniEnv, j_platform),
                             ::djinni::String::toCpp(jniEnv, j_name),
                             ::djinni::String::toCpp(jniEnv, j_pwd));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_com_lxl_demo_gprc_GreeterClient_00024CppProxy_native_1SignIn(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_platform, jstring j_name, jstring j_pwd)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::grpcdemo::GreeterClient>(nativeRef);
        auto r = ref->SignIn(::djinni::String::toCpp(jniEnv, j_platform),
                             ::djinni::String::toCpp(jniEnv, j_name),
                             ::djinni::String::toCpp(jniEnv, j_pwd));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jstring JNICALL Java_com_lxl_demo_gprc_GreeterClient_00024CppProxy_native_1SignUp(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jstring j_name, jstring j_pwd)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::grpcdemo::GreeterClient>(nativeRef);
        auto r = ref->SignUp(::djinni::String::toCpp(jniEnv, j_name),
                             ::djinni::String::toCpp(jniEnv, j_pwd));
        return ::djinni::release(::djinni::String::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace djinni_generated