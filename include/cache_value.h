#ifndef CACHE_VALUE_H
#define CACHE_VALUE_H

#include <string>
#include <any>

#include <redis_handler.h>

class Topic;

class AbstractCacheValue{
protected:
    std::string id_;
    Topic* topic_;
    void removeValueFromRedis_();
    virtual void addValueToRedis_() = 0;
public:
    AbstractCacheValue(std::string, std::string);
    virtual ~AbstractCacheValue() = default;
    std::string getId();
    void setId(std::string);
    Topic* getTopic();
    void changeTopic(std::string);
    std::string toString();
    int toInt();
    float toFloat();
    virtual std::any getValue() = 0;
};

class SimpleCacheValue : public AbstractCacheValue{
protected:
    template <typename T>
    std::any deserialize(T value){
        return std::any_cast<T>(value);
    }

public:
    SimpleCacheValue(std::string, std::string);
    virtual ~SimpleCacheValue() = default;
};

class CacheString : public SimpleCacheValue{
    std::string value_;
    void addValueToRedis_() override;
public:
    CacheString(std::string, std::string);
    CacheString(std::string, std::string, std::string);
    ~CacheString()=default;
    std::any getValue() override;
    void setValue(std::string);
};

#endif // CACHE_VALUE_H