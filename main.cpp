#include <iostream>
#include "src/MysqlConn.h"
#include "src/ConnPool.h"
#include <memory>

void query() {
    MysqlConn conn;
    bool connected = conn.Connect("localhost", "root", "admin", "connpool");
    if (!connected) {
        cerr << "Failed to connect to db" << endl;
        return;
    }
    string sql;
    sql = "insert into table_name (age, name) values (18, 'testmain');";
    bool success = conn.Update(sql);
    cout << "success: " << success << endl;
    sql = "select * from table_name;";
    conn.Query(sql);
    while (conn.Next()) {
        cout << conn.Value(1) << ", "
             << conn.Value(2) << ", " << endl;
    }
}

void op1(int begin, int end) {
    for (int i = begin; i < end; ++i) {
        MysqlConn conn;
        conn.Connect("localhost", "root", "admin", "connpool");
        string sql = "insert into table_name (age, name) values (10, 'one thread, no pool');";
        conn.Update(sql);
    }
}

void op2(ConnPool *pool, int begin, int end) {
    for (int i = begin; i < end; ++i) {
        auto conn = pool->GetConn();
        conn->Connect("localhost", "root", "admin", "connpool");
        string sql = "insert into table_name (age, name) values (10, 'one thread, with pool');";
        conn->Update(sql);
    }
}

void test1(int n) {
    steady_clock::time_point begin = steady_clock::now();
    op1(0, n);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "单线程，无连接池，耗时：" << length.count() / (1000 * 1000) << "ms" << endl;
}

void test2(int n) {
    steady_clock::time_point begin = steady_clock::now();
    op2(ConnPool::Get(), 0, n);
    steady_clock::time_point end = steady_clock::now();
    auto length = end - begin;
    cout << "单线程，带连接池，耗时：" << length.count() / (1000 * 1000) << "ms" << endl;
}

int main() {
    int n = 1000;
    test1(n);
    test2(n);
    return 0;
}
