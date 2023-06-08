#include <cache_value.h>
#include <topic_manager.h>
#include <topic.h>
#include <iostream>

AbstractCacheValue::AbstractCacheValue(std::string id, std::string topic_path){
    id_ = id;
    topic_ = TopicManager::getInstance()->getTopic(topic_path);
}

std::string AbstractCacheValue::getId(){
    return id_;
}

void AbstractCacheValue::setId(std::string id){
    id_ = id;
}

Topic* AbstractCacheValue::getTopic(){
    return topic_;
}

void AbstractCacheValue::changeTopic(std::string new_topic_path){
    TopicManager::getInstance()->changeTopic(id_, topic_->getTopicPath(), new_topic_path);
}

std::string AbstractCacheValue::toString(){
    return std::any_cast<std::string>(getValue());
}

int AbstractCacheValue::toInt(){
    return std::any_cast<int>(getValue());
}

float AbstractCacheValue::toFloat(){
    return std::any_cast<float>(getValue());
}

SimpleCacheValue::SimpleCacheValue(std::string id, std::string topic_path) : AbstractCacheValue(id, topic_path){}

CacheString::CacheString(std::string id, std::string topic_path) : SimpleCacheValue(id, topic_path){
    // TODO same as in another constructor
    TopicManager::getInstance()->getTopic(topic_path)->addCacheValue(this);
}

CacheString::CacheString(std::string id, std::string topic_path, std::string value) : SimpleCacheValue(id, topic_path){
    value_ = value;
    // TODO check if topic exists
    TopicManager::getInstance()->getTopic(topic_path)->addCacheValue(this);
}

std::any CacheString::getValue() {
    // TODO if id in changed parameters then get from redis
    return deserialize(value_);
}

void CacheString::setValue(std::string value){
    value_ = value;
}

void CacheString::addValueToRedis(){
    RedisHandler::getInstance()->set(topic_->getTopicPath() + ":" + id_, value_);
}