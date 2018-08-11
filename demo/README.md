## 后台

- gRPC
- mysql connector

## 客户端

## djinji

用统一的接口文件为各个平台生成相应代码

### Andoid 项目构建

protobuf 三方库需要cherry-pick以下提交才能编译通过(或者打上pb.patch)

~~~
commit abea3ccefee2d7fcb55591754132e7bbbc317212
Author: Yangqing Jia <jiayq84@gmail.com>
Date:   Mon Nov 13 15:15:39 2017 -0800

    Allow one to omit building libprotoc and protoc binaries
~~~