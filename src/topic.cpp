#include <topic.h>
#include <topic_manager.h>

Topic::Topic(std::string topic_path){
    topic_path_ = topic_path;
    TopicManager::addTopic(this);
}

Topic::~Topic(){
    TopicManager::removeTopic(topic_path_);
}

std::string Topic::getTopicPath(){
    return topic_path_;
}