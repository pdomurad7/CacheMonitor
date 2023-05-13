#include <topic_manager.h>

std::map<std::string, Topic*> TopicManager::topics_ = {};

void TopicManager::addTopic(Topic* topic){
    if (topics_.find(topic->getTopicPath()) != topics_.end()){
        topics_.erase(topic->getTopicPath());
    }
    TopicManager::topics_[topic->getTopicPath()] = topic;
};

void TopicManager::removeTopic(std::string topic_path){
    topics_.erase(topic_path);
};

Topic* TopicManager::getTopic(std::string topic_path){
    return topics_[topic_path];
};

std::set<std::string> TopicManager::getTopics(){
    std::set<std::string> topics;
    for (auto topic : topics_){
        topics.insert(topic.first);
    }
    return topics;
};