cmake_minimum_required(VERSION 3.22)
project(mysql_pool)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)

add_executable(mysql_pool main.cpp
        src/MysqlConn.h
        src/MysqlConn.h
        src/ConnPool.h
        src/ConnPool.h
        src/SafeQueue.h
)

target_link_libraries(mysql_pool PRIVATE jsoncpp_lib)
target_link_libraries(mysql_pool PRIVATE mysqlclient)