#ifndef TOPIC_H
#define TOPIC_H

#include <set>
#include <map>

#include <topic_manager.h>
#include <sw/redis++/redis++.h>

class AbstractCacheValue;

class Topic{ // TODO: add mutable and schema, add also update topic (from state in redis)
    std::set<std::string> changed_parameters_;
    std::string topic_path_;
    std::map <std::string, AbstractCacheValue*> cache_values_;
    // sw::redis::Subscriber subscriber_;
    Topic(std::string);
    ~Topic()=default; // should delete all values from redis
    void worker_(float);
    friend class TopicManager;

public:
    Topic(const Topic& other) = delete;
    Topic& operator=(const Topic& other) = delete;
    std::set<std::string> check_changed_parameters();
    void clear_changed_parameters();
    std::string getTopicPath();
    void addCacheValue(AbstractCacheValue*);
    void removeCacheValue(std::string);
    AbstractCacheValue* getCacheValue(std::string);
    bool exists(std::string);
    // void removeCacheValue(AbstractCacheValue*);
};

#endif // TOPIC_H