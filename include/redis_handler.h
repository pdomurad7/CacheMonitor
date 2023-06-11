#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H

#include <sw/redis++/redis++.h>
#include <map>
#include <set>
#include <memory>

class RedisHandler {
    RedisHandler();
    std::map<std::string, std::set<std::string>*> topic_map_;
    static RedisHandler* instance_;
    // std::unique_ptr<sw::redis::Redis> redis_;
    sw::redis::Redis* redis_;
public:
    RedisHandler(const RedisHandler&) = delete;
    RedisHandler& operator=(const RedisHandler&) = delete;
    static RedisHandler* getInstance();
    sw::redis::Redis* getRedis();

};

#endif // REDIS_HANDLER_H
