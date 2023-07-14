#ifndef TOPIC_H
#define TOPIC_H

#include <set>
#include <map>

#include <topic_manager.h>

class AbstractCacheValue;

class Topic{ // TODO: add mutable and schema, add also update topic (from state in redis)
    std::set<std::string> changed_parameters_;
    std::string topic_path_;
    std::map <std::string, AbstractCacheValue*> cache_values_;
    Topic(std::string);
    ~Topic()=default; // should delete all values from redis
    friend class TopicManager;

public:
    Topic(const Topic& other) = delete;
    Topic& operator=(const Topic& other) = delete;
    std::set<std::string> check_changed_parameters();
    void clear_changed_parameters();
    void removeChangedParameter(std::string);
    std::string getTopicPath();
    void addCacheValue(AbstractCacheValue*);
    void removeCacheValue(std::string);
    AbstractCacheValue* getCacheValue(std::string);
    bool exists(std::string);
};

#endif // TOPIC_H