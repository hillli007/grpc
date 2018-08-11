licenses(["notice"])

package(default_visibility = ["//visibility:public"])

load("//bazel:grpc_build_system.bzl", "grpc_proto_library")

grpc_proto_library(
    name = "demo",
    srcs = ["protos/demo.proto"],
)

# cpp 客户端
cc_binary(
    name = "greeter_client",
    srcs = ["cpp/helloworld/greeter_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [":helloworld", "//:grpc++"],
)

# 服务器
cc_binary(
    name = "greeter_server",
    srcs = ["cpp/helloworld/greeter_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [":helloworld", "//:grpc++"],
)
