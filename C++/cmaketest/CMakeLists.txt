cmake_minimum_required (VERSION 3.8)
project (cmaketest)

set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/g++.exe")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")

add_executable(cmaketest a.cc)