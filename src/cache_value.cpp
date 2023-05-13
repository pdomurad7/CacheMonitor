#include <cache_value.h>
#include <topic_manager.h>

AbstractCacheValue::AbstractCacheValue(std::string name, Topic* topic){
    name_ = name;
    topic_ = topic;
    redis_handler_ = &RedisHandler::getInstance();
    };

CacheValue::CacheValue(std::string name, Topic* topic) : AbstractCacheValue(name, topic){};

CacheValue::~CacheValue(){
    std::string path = topic_->getTopicPath() + ":" + name_;
    redis_handler_->del(path);
}

void CacheValue::setName(std::string name){
    name_ = name;
}

std::string CacheValue::getName(){
    return name_;
}

void CacheValue::setValue(std::string value){
    std::string path = topic_->getTopicPath() + ":" + name_;
    redis_handler_->set(path, value);
}

std::string CacheValue::getValue(){
    std::string path = topic_->getTopicPath() + ":" + name_;
    return *redis_handler_->get(path);
}

void CacheValue::setTopic(Topic* topic){
    topic_ = topic;
}

Topic* CacheValue::getTopic(){
    return topic_;
}

void CacheValue::changeTopic(std::string topic_path){
    std::string path = topic_->getTopicPath() + ":" + name_;
    auto val = redis_handler_->get(path);
    redis_handler_->del(path);
    topic_ = TopicManager::getTopic(topic_path);
    path = topic_->getTopicPath() + ":" + name_;
    redis_handler_->set(path, *val);
}

void CacheValue::changeTopic(Topic* topic){
    std::string path = topic_->getTopicPath() + ":" + name_;
    auto val = redis_handler_->get(path);
    redis_handler_->del(path);
    topic_ = topic;
    path = topic_->getTopicPath() + ":" + name_;
    redis_handler_->set(path, *val);
}