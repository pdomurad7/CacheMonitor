#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H

#include <sw/redis++/redis++.h>
#include <map>
#include <set>
#include <memory>
#include <thread>

class RedisHandler {
    RedisHandler();
    std::map<std::string, std::set<std::string>*> topic_map_;
    static RedisHandler* instance_;
    // sw::redis::ConnectionOptions connection_options_;
    // std::shared_ptr<sw::redis::Redis> redis_;
    sw::redis::Redis* redis_;
    // sw::redis::Subscriber sub_ = redis_->subscriber();
    // std::shared_ptr<sw::redis::Subscriber> sub_ptr_;
    sw::redis::Subscriber sub;
    ~RedisHandler();
    sw::redis::ConnectionOptions connection_options_();
    std::thread worker_thread_;
    void worker_(sw::redis::Subscriber&, int);
public:
    RedisHandler(const RedisHandler&) = delete;
    RedisHandler& operator=(const RedisHandler&) = delete;
    static RedisHandler* getInstance();
    sw::redis::Redis* getRedis();

};

#endif // REDIS_HANDLER_H
