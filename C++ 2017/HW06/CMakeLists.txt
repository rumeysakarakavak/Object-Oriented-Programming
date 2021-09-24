cmake_minimum_required(VERSION 3.8)
project(hw6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp GTUSetBase.cpp GTUSetBase.h GTUSet.cpp GTUSet.h GTUMap.cpp GTUMap.h)
add_executable(hw6 ${SOURCE_FILES} GTUSetBase.cpp GTUSetBase.h GTUSet.cpp GTUSet.h GTUMap.cpp GTUMap.h)