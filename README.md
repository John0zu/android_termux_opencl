# android_termux_opencl

## Prepare
1. compile env ubuntu + android sdk ndk
refer to https://github.com/John0zu/ubuntu_install_android_sdk
2. android device and termux app

## target arch settup
in env.sh,you can change *TARGET_ARCHS* to make diffrent ABI.

```shell
#export TARGET_ARCHS=(arm arm64 x86 x86_64)
export TARGET_ARCHS=(arm64)
```

## build libuv
First you need to download libuv-1.43.0.zip yourself.

https://github.com/libuv/libuv.git

also you can change script to get the latest libuv.

./2_build_uv.sh

## build open cl app
application code save in src/main/. You can change main.cmake add new source files.

execute ./3_build_app.sh to make the app.
```shell
$ls src/main/
hello.cl  hello.cpp  hello_cl.h  main.cmake

$./3_build_app.sh
```

##  send the app to termux and run 
the app is exist at output/app/<ABI>/bin/opencl_app
```shell
$ls output/app/arm64-v8a/bin/opencl_app
output/app/arm64-v8a/bin/opencl_app
```
when you copy it to termux, you can get the result:
```shell
~ $ chmod +x opencl_app
~ $ ./opencl_app
Number of platforms:        1

  Index:                    0
  Profile:                  FULL_PROFILE
  Version:                  OpenCL 2.0 QUALCOMM build: commit #50a6870 changeid #I9f59d674eb Date: 07/03/20 Fri Local Branch:  Remote Branch:
  Name:                     QUALCOMM Snapdragon(TM)
  Vendor:                   QUALCOMM
  Extensions:

[2022-05-23 18:51:54.358] Hello  compile program ..
[2022-05-23 18:51:54.416] Hello  compile done
[2022-05-23 18:51:54.425] Hello Read back string: Hello, World!
Hello, World!
```
 
  

