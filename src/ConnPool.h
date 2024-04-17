#ifndef MYSQL_POOL_CONNPOOL_H
#define MYSQL_POOL_CONNPOOL_H

#include <queue>
#include "MysqlConn.h"
#include "jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <condition_variable>
#include <thread>
#include "SafeQueue.h"

using namespace std;
using namespace Json;
using namespace chrono;

const string configFile = "config.json";

class ConnPool {
public:
    static ConnPool *Get() {
        static ConnPool pool;
        return &pool;
    }

    shared_ptr<MysqlConn> GetConn()
    {
        unique_lock<mutex> lock(mu);
        if (conns.empty()) {
            if (consume.wait_for(lock, milliseconds(timeOutMs)) == cv_status::timeout) {
                return nullptr;
            }
        }
        auto conn = std::move(conns.front());
        conns.pop();
        if (conns.size() < dbMinSize) {
            produce.notify_all();
        }
        auto raw = conn.release();
        return shared_ptr<MysqlConn>(raw, [this](MysqlConn* rawConn)
        {
            lock_guard<mutex> lock_guard(mu);
            rawConn->RefreshAliveTime();
            unique_ptr<MysqlConn> unique(rawConn);
            conns.push(std::move(unique));
        });
    }

private:
    queue<unique_ptr<MysqlConn>> conns;
    condition_variable produce;
    condition_variable consume;
    mutex mu;

    string dbIp;
    int dbPort;
    string dbUser;
    string dbPassword;
    string dbName;
    size_t dbMinSize;
    size_t dbMaxSize;
    uint64_t connRecycleIntervalMs;
    uint64_t maxIdleTimeMs;
    uint64_t timeOutMs;

    ConnPool() {
        if (!parseJson()) {
            return;
        }
        addConnUntilMinSize();
        thread producerThread(&ConnPool::producer, this);
        thread recyclerThread(&ConnPool::recycler, this);
        producerThread.detach();
        recyclerThread.detach();
    }

    //删除拷贝构造函数避免创建其他实例
    ConnPool(const ConnPool &obj) = delete;

    //删除复制赋值运算符
    ConnPool &operator=(const ConnPool &obj) = delete;

    bool parseJson() {
        ifstream file(configFile);
        if (!file.is_open()) {
            cerr << "Failed to open " << configFile << endl;
            return false;
        }
        Reader reader;
        Value config;
        reader.parse(file, config);
        if (!config.isObject()) {
            cerr << "Failed to parse " << configFile << endl;
            return false;
        }
        dbIp = config["ip"].asString();
        dbPort = config["port"].asInt();
        dbUser = config["user"].asString();
        dbPassword = config["password"].asString();
        dbName = config["dbName"].asString();
        dbMinSize = config["minSize"].asUInt();
        dbMaxSize = config["maxSize"].asUInt();
        maxIdleTimeMs = config["maxIdleTimeMs"].asUInt64();
        connRecycleIntervalMs = config["connRecycleIntervalMs"].asUInt64();
        timeOutMs = config["timeOutMs"].asUInt64();
        return true;
    }

    void addConnUntilMinSize()
    {
        for (auto i = conns.size(); i < dbMinSize;) {
            auto conn = make_unique<MysqlConn>();
            auto connected = conn->Connect(dbIp, dbUser, dbPassword, dbName, dbPort);
            if (connected) {
                conns.push(std::move(conn));
                ++i;
            } else {
                cerr << "Failed to connect to db" << endl;
            }
        }
    }

    void producer()
    {
        while (true) {
            unique_lock<mutex> lock(mu);
            if (conns.size() < dbMinSize) {
                addConnUntilMinSize();
                //通知消费者资源已准备好
                consume.notify_all();
            }
            else {
                produce.wait(lock); //等待直到其他线程notify唤醒它，等待期间自动释放传入的lock
                //被唤醒时自动重新获取锁
            }
        }
    }

    void recycler()
    {
        while (true) {
            this_thread::sleep_for(chrono::milliseconds(connRecycleIntervalMs));
            unique_lock<mutex> lock(mu);
            while (conns.size() > dbMinSize) {
                if (auto& temp = conns.front(); temp->GetAliveTimeMs() >= maxIdleTimeMs) {
                    conns.pop();
                }
                else {
                    break; //如果最早入队列的线程都没有超时，那就都没超时
                }
            }
        }
    }
};


#endif //MYSQL_POOL_CONNPOOL_H
