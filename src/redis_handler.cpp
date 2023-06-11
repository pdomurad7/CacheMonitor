#include <redis_handler.h>
#include <topic_manager.h>

RedisHandler::RedisHandler(){
    sw::redis::ConnectionOptions connection_options;
    connection_options.host = "127.0.0.1";
    connection_options.port = 6379;
    // std::unique_ptr<sw::redis::Redis> redis_ = std::make_unique<sw::redis::Redis>(connection_options);
    redis_ = new sw::redis::Redis(connection_options); // TODO change to unique_ptr
}

RedisHandler *RedisHandler::instance_ = nullptr;

RedisHandler *RedisHandler::getInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new RedisHandler();
    }
    return instance_;
}

sw::redis::Redis *RedisHandler::getRedis()
{
    return redis_;
    // return redis_.get();
}
