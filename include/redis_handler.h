#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H

#include <sw/redis++/redis++.h>
#include <map>
#include <set>
#include <memory>
#include <thread>
#include <atomic>

class RedisHandler {
    static RedisHandler instance_;
    std::shared_ptr<sw::redis::Redis> redis_;
    sw::redis::Subscriber sub_;
    std::atomic<bool> stop_worker_;
    sw::redis::ConnectionOptions connection_options_();
    std::thread worker_thread_;
    void worker_(sw::redis::Subscriber&, int, const std::atomic<bool>&);
    RedisHandler();
public:
    ~RedisHandler();
    RedisHandler(const RedisHandler&) = delete;
    RedisHandler& operator=(const RedisHandler&) = delete;
    static RedisHandler& getInstance();
    sw::redis::Redis* getRedis();

};

#endif // REDIS_HANDLER_H
