#ifndef CACHE_VALUE_H
#define CACHE_VALUE_H

#include <string>
#include <topic.h>
#include <redis_handler.h>

class AbstractCacheValue{
protected:
    std::string name_;
    Topic* topic_;
    RedisHandler* redis_handler_;

public:
    AbstractCacheValue(std::string name, Topic* topic);
    // virtual ~AbstractCacheValue();
    virtual std::string getName() = 0;
    virtual void setName(std::string name) = 0;
    virtual Topic* getTopic() = 0;
    virtual void setTopic(Topic* topic) = 0;
    virtual void changeTopic(std::string topic_path) = 0;
    virtual void changeTopic(Topic* topic) = 0;
};

class CacheValue : private AbstractCacheValue{ // TEMPORARY SUPPORT ONLY STRING VALUES
public:
    CacheValue(std::string name, Topic* topic);
    ~CacheValue();
    std::string getName();
    void setName(std::string name);
    Topic* getTopic();
    void setTopic(Topic* topic);
    void changeTopic(std::string topic_path);
    void changeTopic(Topic* topic);
    // TODO change to template
    void setValue(std::string value);
    std::string getValue();
};

#endif // CACHE_VALUE_H