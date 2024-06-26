### 项目介绍
使用C++11实现了一个MySQL线程池，通过线程池来管理数据库连接，可以有效避免数据库连接频繁的创建和销毁所带来的性能开销，项目使用RAII机制和智能指针实现资源和内存管理，保证了资源和内存的正确回收释放，同时确保了在数据库连接使用完毕时，该连接会自动回到连接池，提高易用性；使用互斥锁和条件变量实现了生产者-消费者模型，用于管理数据库连接的创建和使用。添加了jsoncpp库以支持动态解析数据库配置文件。
### 测试结果（release）
| N | 无线程池 | 带线程池 |
|:----:| :----:| :----:|
| 1000 | 3049ms | 1494ms |
| 2000 | 5910ms | 2999ms |
| 5000 | 14833ms | 7466ms |
