cmake_minimum_required(VERSION 3.22)
project(mysql_pool)

set(CMAKE_CXX_STANDARD 17)

add_executable(mysql_pool main.cpp
        src/MysqlConn.h
        src/MysqlConn.h
)
