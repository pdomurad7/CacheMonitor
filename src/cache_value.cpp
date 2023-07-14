#include <cache_value.h>
#include <topic_manager.h>
#include <topic.h>
#include <iostream>

AbstractCacheValue::AbstractCacheValue(std::string id, std::string topic_path){
    id_ = id;
    topic_ = TopicManager::getInstance().getTopic(topic_path);
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
    // TODO: handling changing on non existing topic
    std::string old_topic_path = topic_->getTopicPath();
    removeValueFromRedis_();
    topic_ = TopicManager::getInstance().getTopic(new_topic_path);
    TopicManager::getInstance().changeTopic(id_, old_topic_path, new_topic_path);
    addValueToRedis_();
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

void AbstractCacheValue::removeValueFromRedis_(){
    RedisHandler::getInstance().getRedis()->del(topic_->getTopicPath() + ":" + id_);
}

SimpleCacheValue::SimpleCacheValue(std::string id, std::string topic_path) : AbstractCacheValue(id, topic_path){}


CacheString::CacheString(std::string id, std::string topic_path) : SimpleCacheValue(id, topic_path){
    // TODO same as in another constructor
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

CacheString::CacheString(std::string id, std::string topic_path, std::string value) : SimpleCacheValue(id, topic_path){
    value_ = value;
    // TODO check if topic exists
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

std::any CacheString::getValue() {
    if (TopicManager::getInstance().getTopic(topic_->getTopicPath())->exists(id_)) {
        value_ = *RedisHandler::getInstance().getRedis()->get(topic_->getTopicPath() + ":" + id_);
        topic_->removeChangedParameter(id_);
    }
    return deserialize(value_);
}

void CacheString::setValue(std::string value){
    value_ = value;
    addValueToRedis_();
}

void CacheString::addValueToRedis_(){
    RedisHandler::getInstance().getRedis()->set(topic_->getTopicPath() + ":" + id_, value_);
}


CacheInt::CacheInt(std::string id, std::string topic_path) : SimpleCacheValue(id, topic_path){
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

CacheInt::CacheInt(std::string id, std::string topic_path, int value) : SimpleCacheValue(id, topic_path){
    value_ = value;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

std::any CacheInt::getValue() {
    if (TopicManager::getInstance().getTopic(topic_->getTopicPath())->exists(id_)) {
        value_ = std::stoi(*RedisHandler::getInstance().getRedis()->get(topic_->getTopicPath() + ":" + id_));
        topic_->removeChangedParameter(id_);
    }
    return deserialize(value_);
}

void CacheInt::setValue(int value){
    value_ = value;
    addValueToRedis_();
}

void CacheInt::addValueToRedis_(){
    RedisHandler::getInstance().getRedis()->set(topic_->getTopicPath() + ":" + id_, std::to_string(value_));
}

CacheFloat::CacheFloat(std::string id, std::string topic_path) : SimpleCacheValue(id, topic_path){
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

CacheFloat::CacheFloat(std::string id, std::string topic_path, float value) : SimpleCacheValue(id, topic_path){
    value_ = value;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

std::any CacheFloat::getValue() {
    if (TopicManager::getInstance().getTopic(topic_->getTopicPath())->exists(id_)) {
        value_ = std::stof(*RedisHandler::getInstance().getRedis()->get(topic_->getTopicPath() + ":" + id_));
        topic_->removeChangedParameter(id_);
    }
    return deserialize(value_);
}

void CacheFloat::setValue(float value){
    value_ = value;
    addValueToRedis_();
}

void CacheFloat::addValueToRedis_(){
    RedisHandler::getInstance().getRedis()->set(topic_->getTopicPath() + ":" + id_, std::to_string(value_));
}