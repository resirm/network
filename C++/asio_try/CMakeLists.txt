cmake_minimum_required (VERSION 3.8)
project (Asio_try)

set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/g++.exe")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o client")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")

# 版本号信息
# set (CHAT_VERSION_MAJOR 0)
# set (CHAT_VERSION_MINOR 1)
 
# 配置一个头文件，从而将CMake的一些设置传递到源文件中。
# 以chat_config.h.in为模板，生成chat_config.h
# configure_file (
#   "${PROJECT_SOURCE_DIR}/chat_config.h.in"
#   "${PROJECT_BINARY_DIR}/chat_config.h"
# )

# 将构建目录添加到include的搜索路径中
# 这样就能够找到chat_config.h
# include_directories("${PROJECT_BINARY_DIR}")
# asio path
include_directories("E:/Coding/lib/asio-1.12.2/include")

add_definitions(-DASIO_STANDALONE -DASIO_HAS_STD_ADDRESSOF -DASIO_HAS_STD_ARRAY
-DASIO_HAS_CSTDINT -DASIO_HAS_STD_SHARED_PTR -DASIO_HAS_STD_TYPE_TRAITS
-DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB)

link_libraries(ws2_32 wsock32)

add_executable(Asio_try async.cc)