#include <chrono>
#include <thread>
#include <sstream>

#include <redis_handler.h>
#include <topic_manager.h>

RedisHandler::RedisHandler() : Redis("tcp://127.0.0.1:6379") {}

RedisHandler *RedisHandler::instance_ = nullptr;

RedisHandler *RedisHandler::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new RedisHandler();
    }
    return instance_;
}
