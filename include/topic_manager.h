#ifndef TOPIC_MANAGER_H
#define TOPIC_MANAGER_H

#include <map>
#include <string>
#include <topic.h>

class TopicManager {
    static std::map<std::string, Topic*> topics_;
public:
    static Topic* getTopic(std::string topic_path);
    static void addTopic(Topic* topic);
    static void removeTopic(std::string topic_path);
    static std::set<std::string> getTopics();
};

#endif // TOPIC_MANAGER_H