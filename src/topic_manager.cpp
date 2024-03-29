#include <topic_manager.h>
#include <topic.h>
#include <redis_handler.h>
#include <iostream>

TopicManager& TopicManager::getInstance()
{
    static TopicManager instance_;
    return instance_;
}

Topic* TopicManager::getTopic(std::string topic_path){
    if(topics_.find(topic_path) != topics_.end())
        return topics_[topic_path];
    return nullptr;
}

void TopicManager::createTopic(std::string topic_path){
    topics_[topic_path] = new Topic(topic_path);
}

void TopicManager::removeTopic(std::string topic_path){
    delete topics_[topic_path];
    topics_.erase(topic_path);
    RedisHandler::getInstance().getRedis()->del(topic_path);
}

void TopicManager::changeTopic(std::string id, std::string old_topic_path, std::string new_topic_path){
    topics_[new_topic_path]->addCacheValue(topics_[old_topic_path]->cache_values_[id]);
    topics_[old_topic_path]->cache_values_.erase(id);
}

bool TopicManager::exists(std::string topic_path){
    return topics_.find(topic_path) != topics_.end();
}

void TopicManager::addChangedParameter(std::string topic_path, std::string parameter){
    if (!exists(topic_path))
        return;
    topics_[topic_path]->changed_parameters_.insert(parameter);
}