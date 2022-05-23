#!/bin/bash
set -e

source env.sh

args="--api 29 --stl=libc++"


for arch in ${TARGET_ARCHS[@]}; do
    if [ ! -d "$NDK_TOOL_DIR/$arch" ]; then
        echo "installing $ANDROID_NDK_ROOT $arch $args"
        python $ANDROID_NDK_ROOT/build/tools/make_standalone_toolchain.py $args --arch $arch --install-dir $NDK_TOOL_DIR/$arch
        sed -i.orig "s|using ::fgetpos;|//using ::fgetpos;|" $NDK_TOOL_DIR/$arch/include/c++/4.9.x/cstdio
        sed -i.orig "s|using ::fsetpos;|//using ::fsetpos;|" $NDK_TOOL_DIR/$arch/include/c++/4.9.x/cstdio
    fi
done

