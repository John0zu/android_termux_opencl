set(HEADERS_ANDROID_OPENCL
	src/android_opencl/OclDevice.h
	src/android_opencl/OclError.h
	src/android_opencl/OclKernel.h
	src/android_opencl/OclLib.h
	src/android_opencl/OclPlatform.h
	src/android_opencl/OclVendor.h
	src/android_opencl/String.h
	src/android_opencl/Log.h
	)

set(SOURCES_ANDROID_OPENCL
	src/android_opencl/OclDevice.cpp
	src/android_opencl/OclError.cpp
	src/android_opencl/OclKernel.cpp
	src/android_opencl/OclLib.cpp
	src/android_opencl/OclPlatform.cpp
	src/android_opencl/String.cpp
	src/android_opencl/Log.cpp
	)

include_directories(src/android_opencl)

