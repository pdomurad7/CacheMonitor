#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H

#include <sw/redis++/redis++.h>
#include <map>
#include <set>

class RedisHandler : public sw::redis::Redis {
    RedisHandler();
    std::map<std::string, std::set<std::string>*> topic_map_;
public:
    RedisHandler(const RedisHandler&) = delete;
    RedisHandler& operator=(const RedisHandler&) = delete;

    static RedisHandler& getInstance();
};

#endif // REDIS_HANDLER_H
