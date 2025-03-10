cmake_minimum_required(VERSION 3.2)
project(TinyBridge)

add_definitions(-DDEBUG)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_HTTPD 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/HTTPD/*.cpp 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/message/*.cpp)
add_executable(HTTPD ${SRC_HTTPD})

file(GLOB_RECURSE SRC_TRANSACTION 
     ${CMAKE_CURRENT_SOURCE_DIR}/src/transaction/*.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/message/*.cpp)
add_executable(transaction ${SRC_TRANSACTION})