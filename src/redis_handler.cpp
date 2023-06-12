#include <redis_handler.h>
#include <topic_manager.h>
#include <iostream>

RedisHandler::RedisHandler(){
    redis_ = new sw::redis::Redis(connection_options_()); // TODO change to unique_ptr
    redis_->command("config", "set", "notify-keyspace-events", "KEA");
    // sw::redis::Subscriber sub = redis_->subscriber();
    sub = redis_->subscriber();
    sub.psubscribe("__keyspace@0__:*");
    sub.on_pmessage([](std::string pattern, std::string channel, std::string msg) {
        std::istringstream msgstream(channel);
        std::getline(msgstream, channel, ':');
        std::string topic_path;
        std::string value_id;

        std::getline(msgstream, topic_path, ':');
        std::getline(msgstream, value_id, ':');

        TopicManager::getInstance()->addChangedParameter(topic_path, value_id);
    });
    // worker_thread_ = std::thread(&RedisHandler::worker_, this, std::ref(sub), 1000);

}

RedisHandler *RedisHandler::instance_ = nullptr;

RedisHandler *RedisHandler::getInstance()
{
    if (instance_ == nullptr)
    { 
        instance_ = new RedisHandler();

        //     RedisHandler::getInstance()->getRedis()->command("config", "set", "notify-keyspace-events", "KEA");
//     auto sub = RedisHandler::getInstance()->getRedis()->subscriber();
//     sub.psubscribe("__keyspace@0__:*");
//     sub.on_pmessage([](std::string pattern, std::string channel, std::string msg) {
//         std::istringstream msgstream(channel);
//         std::getline(msgstream, channel, ':');
//         std::string topic_path;
//         std::string value_id;

//         std::getline(msgstream, topic_path, ':');
//         std::getline(msgstream, value_id, ':');

//         TopicManager::getInstance()->addChangedParameter(topic_path, value_id);
//     });
    }
    return instance_;
}

sw::redis::Redis* RedisHandler::getRedis()
{
    return redis_;
    // return redis_.get();
}

RedisHandler::~RedisHandler(){
    // delete redis_;
}

sw::redis::ConnectionOptions RedisHandler::connection_options_(){
    sw::redis::ConnectionOptions connection_options;
    connection_options.host = "127.0.0.1";
    connection_options.port = 6379;
    connection_options.db = 0;
    return connection_options;
}

void RedisHandler::worker_(sw::redis::Subscriber& sub_ptr, int interval){
    while(true){
        sub_ptr.consume();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}