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

class CacheInt : public SimpleCacheValue {
    int value_;
    void addValueToRedis_() override;

public:
    CacheInt(std::string, std::string);
    CacheInt(std::string, std::string, int);
    ~CacheInt() = default;
    std::any getValue() override;
    void setValue(int value);
};
class CacheFloat : public SimpleCacheValue {
    float value_;
    void addValueToRedis_() override;

public:
    CacheFloat(std::string, std::string);
    CacheFloat(std::string, std::string, float);
    ~CacheFloat() = default;
    std::any getValue() override;
    void setValue(float value);
};
#endif // CACHE_VALUE_H