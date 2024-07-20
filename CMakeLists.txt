cmake_minimum_required(VERSION 3.22)
project(SvenBXT)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS -m32)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS -m32)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package( Threads REQUIRED )

# Link with dependencies
target_link_libraries(
        Threads::Threads
)

add_library(SvenBXT SHARED
        SvenBXT.cpp
        SvenBXT.h
        Utils.cpp
        Utils.h
        hlsdk_mini.hpp)
