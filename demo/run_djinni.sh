#! /usr/bin/env bash
 
base_dir=$(cd "`dirname "0"`" && pwd)

# cpp 客户端, 生成共用的c++接口,代码自己实现
cpp_out="$base_dir/cpp-client"
namespace="grpcdemo"

# android 客户端, 包括java和jni
jni_out="$base_dir/android-client/app/src/main/cpp"
java_out="$base_dir/android-client/app/src/main/java/com/lxl/demo/gprc"
java_package="com.lxl.demo.gprc"

# 接口文件
djinni_file="greeter.djinni"
 
djinni/src/run \
   --java-out $java_out \
   --java-package $java_package \
   --ident-java-field mFooBar \
   \
   --jni-out $jni_out \
   --ident-jni-class NativeFooBar \
   --ident-jni-file NativeFooBar \
   \
   --cpp-out $cpp_out \
   --cpp-namespace $namespace \
   \
   --idl $djinni_file