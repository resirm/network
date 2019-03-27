cmake_minimum_required (VERSION 3.8)
project (client)

set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/g++.exe")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o client -I E:/Coding/lib/asio-1.12.2/include")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static")

add_definitions(-DASIO_STANDALONE -DASIO_HAS_STD_ADDRESSOF -DASIO_HAS_STD_ARRAY
-DASIO_HAS_CSTDINT -DASIO_HAS_STD_SHARED_PTR -DASIO_HAS_STD_TYPE_TRAITS
-DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB)

link_libraries(ws2_32 wsock32)

add_executable(client chat_client.cc)