cmake_minimum_required(VERSION 2.8.12)
project(opencl_app)

set(WITH_OPENCL_VERSION 200 CACHE STRING "Target OpenCL version")


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package(UV REQUIRED)


include (CheckIncludeFile)



include (src/android_opencl/android_opencl.cmake)
include (src/main/main.cmake)
include_directories(src)
include_directories(${UV_INCLUDE_DIR})

set(SOURCES
	"${SOURCES_ANDROID_OPENCL}"
	"${SOURCES_MAIN_OPENCL}"
)
set(HEADERS
    "${HEADERS_ANDROID_OPENCL}"
    "${HEADERS_MAIN_OPENCL}"
)

#set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}  ${UV_LIBRARIES})
install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_DIR})
