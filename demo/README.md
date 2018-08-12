## 后台

### gRPC 

定义protobuf, 这里定义注册/登录/登出/心跳 接口, 请求消息包含设备/用户名/密码(加密), 响应消息则是简单的一条字符串

~~~
syntax = "proto3";

option java_multiple_files = true;
option java_package = "com.lxl.demo.grpc";
option java_outer_classname = "DemoProto";
option objc_class_prefix = "LXL";

package demo;

service Greeter {
  rpc SignUp (DemoRequest) returns (DemoReply) {}
  rpc SignIn (DemoRequest) returns (DemoReply) {}
  rpc LogOut (DemoRequest) returns (DemoReply) {}
  rpc HeartBeat (DemoRequest) returns (DemoReply) {}
}

message DemoRequest {
  string platform = 1;
  string username = 2;
  string pwd = 3;
}

message DemoReply {
  string message = 1;
}

~~~

### MySQL

后台采用MySQL,采用JDBC的C++版本来通信

数据库包含id/用户名/密码(加密)/登录设备, 暂时不考虑同一平台多个设备的情况

~~~
CREATE TABLE `users` (
  `id_users` int(11) NOT NULL AUTO_INCREMENT,
  `user_name` varchar(45) DEFAULT NULL,
  `pwd` varchar(45) DEFAULT NULL,
  `online` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`id_users`),
  UNIQUE KEY `id_users_UNIQUE` (`id_users`),
  UNIQUE KEY `user_name_UNIQUE` (`user_name`)
) ENGINE=InnoDB AUTO_INCREMENT=29 DEFAULT CHARSET=latin1;
~~~

## 客户端

### djinji

用统一的接口文件为各个平台生成相应代码

~~~
greeter_client = interface +c {
    HeartBeat(platform:string ,name:string , pwd:string): string;
    LogOut(platform:string ,name:string , pwd:string): string;
    SignIn(platform:string ,name:string , pwd:string): string;
    SignUp(name:string , pwd:string): string;
}
~~~

生成各个平台代码

~~~
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
~~~

djinni帮忙生成接口,具体功能由实现,做到各个平台使用统一的C++代码

### Andoid 项目构建

Android 采用Cmake来编译本地代码

- 用proto生成相关代码,包括服务和消息的头文件和实现文件
- 用生成的proto代码编译库
- 编译jni库,注意需要加入djinni的支持库

protobuf 三方库需要cherry-pick以下提交才能编译通过(或者打上pb.patch)

~~~
commit abea3ccefee2d7fcb55591754132e7bbbc317212
Author: Yangqing Jia <jiayq84@gmail.com>
Date:   Mon Nov 13 15:15:39 2017 -0800

    Allow one to omit building libprotoc and protoc binaries
~~~

### 设备不能同时在线的实现方案

登录时只做合法用户检查,客户端登录后采取心跳机制来检查在线状态,如果心跳检查出在线状态不是当前设备则提示被挤出.

## Bazel 构建和项目管理

- 定义BUILD, gRPC已定义相关规则
- 编译: bazel build //demo:cpp-server
