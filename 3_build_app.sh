set -e

source env.sh

if [ -e $TARGET_BUILD_DIR/app ] ; then
	rm -fr $TARGET_BUILD_DIR/app
fi
if [ -e $TARGET_INSTALL_DIR/app ] ; then
	rm -fr $TARGET_INSTALL_DIR/app
fi




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

    mkdir -p $TARGET_BUILD_DIR/app/$ANDROID_ABI
    cd $TARGET_BUILD_DIR/app/$ANDROID_ABI
    
    TARGET_DIR=$TARGET_INSTALL_DIR/app/$ANDROID_ABI


    mkdir -p $TARGET_DIR
    echo "- Building for ${arch} (${ANDROID_ABI})"

    $CMAKE -DCMAKE_TOOLCHAIN_FILE=$TOOLCHAIN \
        -DANDROID_ABI="$ANDROID_ABI" \
        -DANDROID_PLATFORM=$ANDROID_PLATFORM \
        -DCL_TARGET_OPENCL_VERSION=200 \
        -DCMAKE_INSTALL_PREFIX=$TARGET_DIR \
		-DUV_LIBRARY="$TARGET_INSTALL_DIR/libuv/$ANDROID_ABI/lib/libuv_a.a" \
        -DUV_INCLUDE_DIR="$TARGET_INSTALL_DIR/libuv/$ANDROID_ABI/include"  \
         ../../../ &&  make && make install

done

exit 0
