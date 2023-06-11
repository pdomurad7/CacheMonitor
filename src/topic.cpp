#include <topic.h>
#include <redis_handler.h>
#include <cache_value.h>
#include <iostream>

Topic::Topic(std::string topic_path){
    topic_path_ = topic_path;
}

std::string Topic::getTopicPath(){
    return topic_path_;
}

std::set<std::string> Topic::check_changed_parameters(){
    return changed_parameters_;
}

void Topic::clear_changed_parameters(){
    changed_parameters_.clear();
}

void Topic::addCacheValue(AbstractCacheValue* cache_value){
    cache_values_[cache_value->getId()] = cache_value;
}

void Topic::removeCacheValue(std::string id){
    delete cache_values_[id];
    cache_values_.erase(id);
    RedisHandler::getInstance()->getRedis()->del(topic_path_ + ":" + id);
}

AbstractCacheValue* Topic::getCacheValue(std::string id){
    return cache_values_[id];
}

bool Topic::exists(std::string id){
    return cache_values_.find(id) != cache_values_.end();
}
