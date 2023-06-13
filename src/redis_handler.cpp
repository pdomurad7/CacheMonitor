#include <redis_handler.h>
#include <topic_manager.h>
#include <iostream>

RedisHandler::RedisHandler() : redis_(std::make_unique<sw::redis::Redis>(connection_options_())),
                               sub_(redis_->subscriber()),
                               stop_worker_(false)
{
    redis_->command("config", "set", "notify-keyspace-events", "KEA");
    sub_.psubscribe("__keyspace@0__:*");
    sub_.on_pmessage([](std::string pattern, std::string channel, std::string msg)
                     {
        std::istringstream msgstream(channel);
        std::getline(msgstream, channel, ':');
        std::string topic_path;
        std::string value_id;

        std::getline(msgstream, topic_path, ':');
        std::getline(msgstream, value_id, ':');

        TopicManager::getInstance().addChangedParameter(topic_path, value_id); });
    worker_thread_ = std::thread(&RedisHandler::worker_, this, std::ref(sub_), 1, std::ref(stop_worker_));
}

RedisHandler::~RedisHandler()
{
    stop_worker_ = true;
    worker_thread_.join();
}

RedisHandler &RedisHandler::getInstance()
{
    static RedisHandler instance_;
    return instance_;
}

sw::redis::Redis *RedisHandler::getRedis()
{
    return redis_.get();
}

sw::redis::ConnectionOptions RedisHandler::connection_options_()
{
    sw::redis::ConnectionOptions connection_options;
    connection_options.host = "127.0.0.1";
    connection_options.port = 6379;
    connection_options.db = 0;
    return connection_options;
}

void RedisHandler::worker_(sw::redis::Subscriber &sub_ptr, int interval, const std::atomic<bool> &stop_worker_)
{
    while (stop_worker_)
    {
        sub_ptr.consume();
        std::this_thread::sleep_for(std::chrono::seconds(interval));
    }
}