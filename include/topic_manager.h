#ifndef TOPIC_MANAGER_H
#define TOPIC_MANAGER_H

#include <map>
#include <string>

class Topic;

class TopicManager {
    TopicManager(const TopicManager&) = delete;
    TopicManager& operator=(const TopicManager&) = delete;
    TopicManager()=default;
    std::map<std::string, Topic*> topics_;
    static TopicManager* instance_;
public:
    static TopicManager* getInstance();
    Topic* getTopic(std::string);
    void createTopic(std::string);
    void removeTopic(std::string);
    void changeTopic(std::string, std::string, std::string);
};

#endif // TOPIC_MANAGER_H