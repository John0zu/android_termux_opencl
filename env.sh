realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

if [ -z $ANDROID_HOME -o  ! -d $ANDROID_HOME ] ; then
    echo "ANDROID_HOME not define in env, did you install android sdk?"
    exit 1
fi

export NDK_VERSION=`$ANDROID_HOME/cmdline-tools/latest/bin/sdkmanager --list_installed | grep "ndk;" |  head -n 1 | sed -E 's/(.*)(ndk\/)([0-9\.])/\3/' | xargs`

if [ -z $NDK_VERSION ] ; then
    echo Not found NDK tools
    exit 2
fi


ANDROID_NDK_ROOT="${ANDROID_HOME}/ndk/${NDK_VERSION}"
export ANDROID_NDK_ROOT=`realpath $ANDROID_NDK_ROOT`

TARGET_BUILD_DIR=`pwd`/build/
TARGET_INSTALL_DIR=`pwd`/output


DEFAULT_NDK_TOOL_DIR=${TARGET_BUILD_DIR}/tool/
NDK_TOOL_DIR="${NDK_TOOL_DIR:-${DEFAULT_NDK_TOOL_DIR}}"
export NDK_TOOL_DIR=${NDK_TOOL_DIR%/}


#export TARGET_ARCHS=(arm arm64 x86 x86_64)
export TARGET_ARCHS=(arm64)

export TOOLCHAIN=$ANDROID_HOME/ndk/$NDK_VERSION/build/cmake/android.toolchain.cmake
export CMAKE=$ANDROID_HOME/cmake/3.18.1/bin/cmake
export ANDROID_PLATFORM=android-29


