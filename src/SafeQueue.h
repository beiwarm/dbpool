#ifndef MYSQL_POOL_SAFEQUEUE_H
#define MYSQL_POOL_SAFEQUEUE_H

#include <mutex>
#include <queue>

using namespace std;

template<typename T>
class SafeQueue {
private:
    queue<T> queue;
    recursive_mutex mu;

public:
    bool Empty() // 返回队列是否为空
    {
        unique_lock<recursive_mutex> lock(mu);
        return queue.empty();
    }

    size_t Size() {
        unique_lock<recursive_mutex> lock(mu);
        return queue.size();
    }

    void Push(const T &t) {
        unique_lock<recursive_mutex> lock(mu);
        queue.push(t);
    }

    //支持移动语义
    void Push(T &&t) {
        unique_lock<recursive_mutex> lock(mu);
        queue.push(std::move(t));
    }

    // 队列取出元素
    bool Pop(T &t) {
        unique_lock<recursive_mutex> lock(mu);
        if (queue.empty())
            return false;
        t = move(queue.front());
        queue.pop();
        return true;
    }
};

#endif //MYSQL_POOL_SAFEQUEUE_H
