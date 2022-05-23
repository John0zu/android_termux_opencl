set -e

source env.sh

if [ -e $TARGET_BUILD_DIR/libuv ] ; then
	rm -fr $TARGET_BUILD_DIR/libuv
fi
if [ -e $TARGET_INSTALL_DIR/libuv ] ; then
	rm -fr $TARGET_INSTALL_DIR/libuv
fi


if [ -e libuv-1.43.0 ] ; then
	rm -fr libuv-1.43.0
fi

if [ ! -e libuv-1.43.0.zip ] ;then
    echo "Please download libuv at https://github.com/libuv/libuv.git"
    exit 1
fi

if [ ! -e $TARGET_BUILD_DIR ] ; then
    mkdir -p $TARGET_BUILD_DIR
fi

unzip libuv-1.43.0.zip > /dev/null

mv libuv-1.43.0 $TARGET_BUILD_DIR/libuv


for arch in ${TARGET_ARCHS[@]}; do
    case ${arch} in
        "arm")
            target_host=arm-linux-androideabi
            ANDROID_ABI="armeabi-v7a"
            ;;
        "arm64")
            target_host=aarch64-linux-android
            ANDROID_ABI="arm64-v8a"
            ;;
        "x86")
            target_host=i686-linux-android
            ANDROID_ABI="x86"
            ;;
        "x86_64")
            target_host=x86_64-linux-android
            ANDROID_ABI="x86_64"
            ;;
        *)
            exit 16
            ;;
    esac

    mkdir -p $TARGET_BUILD_DIR/libuv/build/$ANDROID_ABI
    cd $TARGET_BUILD_DIR/libuv/build/$ANDROID_ABI
    
    TARGET_DIR=$TARGET_INSTALL_DIR/libuv/$ANDROID_ABI

    if [ -f "$TARGET_DIR/lib/libuv.la" ]; then
      continue
    fi

    mkdir -p $TARGET_DIR
    echo "- Building for ${arch} (${ANDROID_ABI})"

    $CMAKE -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN \
        -DANDROID_ABI="$ANDROID_ABI" \
        -DANDROID_PLATFORM=$ANDROID_PLATFORM \
        -DCMAKE_INSTALL_PREFIX=$TARGET_DIR \
        -DBUILD_SHARED_LIBS=OFF \
        ../../ \
        && make -j 4 \
        && make install \
        && make clean

done

exit 0
