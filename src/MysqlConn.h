#ifndef MYSQL_POOL_MYSQLCONN_H
#define MYSQL_POOL_MYSQLCONN_H

#include <string>
#include "mysql/mysql.h"
#include <memory>

using namespace std;

class MysqlConn {
    //初始化数据库连接
public:
    MysqlConn() {
        conn = mysql_init(nullptr);
        mysql_set_character_set(conn, "utf8mb4");
    }

    ~MysqlConn() {
        if (conn != nullptr) {
            mysql_close(conn);
            conn = nullptr;
        }
    }

    bool Connect(const string &ip, const string &user, const string &password, const string &dbName = "",
                 int port = 3306) {
        return mysql_real_connect(conn, ip.c_str(), user.c_str(), password.c_str(),
                                  dbName.c_str(), port, nullptr, 0)
               != nullptr;
    }

    bool Update(const string &sql) {
        return mysql_query(conn, sql.c_str()) == 0;
    }

    bool Query(const string &sql) {
        if (mysql_query(conn, sql.c_str()) != 0) {
            return false;
        }
        result.reset(mysql_store_result(conn));
        return true;
    }

    bool Next() {
        if (result != nullptr) {
            row = mysql_fetch_row(result.get());
            return true;
        }
        return false;
    }

    string Value(uint fieldIndex) {
        uint colCount = mysql_num_fields(result.get());
        if (fieldIndex >= colCount) {
            return "";
        }
        char *val = row[fieldIndex]; //取该行的第x列的数据
        ulong dataLength = mysql_fetch_lengths(result.get())[fieldIndex];
        //避免直接用char*创建string时，遇到\0就结束可能会截断数据的问题
        return string(val, dataLength);
    }

    bool Transaction() {
        return mysql_autocommit(conn, false);
    }

    bool Commit() {
        return mysql_commit(conn);
    }

    bool Rollback() {
        return mysql_rollback(conn);
    }

private:
    MYSQL *conn = nullptr; //RAII，构造函数赋值，析构函数释放
    //unique_ptr想要一个指向deleter的指针，这边传一个指向free函数的指针
    unique_ptr<MYSQL_RES, decltype(&mysql_free_result)> result{nullptr, mysql_free_result}; //智能指针自动释放查询结果
    MYSQL_ROW row = nullptr; //不需要单独释放，因为result释放的时候row的内存也就释放了
};


#endif //MYSQL_POOL_MYSQLCONN_H
