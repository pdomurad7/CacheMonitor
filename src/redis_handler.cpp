#include <redis_handler.h>
#include <sw/redis++/redis++.h>

RedisHandler::RedisHandler() : Redis("tcp://127.0.0.1:6379") {}

RedisHandler& RedisHandler::getInstance() {
    static RedisHandler instance;
    return instance;
}
