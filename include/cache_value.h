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
    std::list<std::string> toList();
    std::map<std::string, std::string> toMap();
    std::set<std::string> toSet();
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

class ContainerCacheValue : public AbstractCacheValue{
public:
    ContainerCacheValue(std::string, std::string);
    virtual ~ContainerCacheValue() = default;
    virtual void clear() = 0;
    virtual int size() = 0;
    virtual bool contains(std::string) = 0;
    virtual bool empty() = 0;
};

class CacheList : public ContainerCacheValue{
    std::list<std::string> value_;
    void addValueToRedis_() override;
public:
    CacheList(std::string, std::string, std::list<std::string>);
    ~CacheList() = default;
    std::any deserialize(std::list<std::string>);
    std::any getValue() override;
    void setValue(std::list<std::string>);
    void rpush(std::string);
    void lpush(std::string);
    std::string rpop();
    std::string lpop();
    int size() override;
    bool contains(std::string) override;
    bool empty() override;
    void clear() override;
};

class CacheMap : public ContainerCacheValue{
    std::map<std::string, std::string> value_;
    void addValueToRedis_() override;
public:
    CacheMap(std::string, std::string, std::map<std::string, std::string>);
    ~CacheMap() = default;
    std::any deserialize(std::map<std::string, std::string>);
    std::any getValue() override;
    void setValue(std::map<std::string, std::string>);
    void addKey(std::string, std::string);
    void eraseKey(std::string);
    std::string getKey(std::string);
    int size() override;
    bool contains(std::string) override;
    bool empty() override;
    void clear() override;
};

class CacheSet : public ContainerCacheValue {
private:
    std::set<std::string> value_;
    void addValueToRedis_() override;

public:
    CacheSet(std::string id, std::string topic_path, std::set<std::string> value);
    ~CacheSet() = default;

    std::any deserialize(std::set<std::string> value);
    std::any getValue() override;
    void setValue(std::set<std::string> value);
    void addValue(std::string val);
    void removeValue(std::string val);
    bool contains(std::string val) override;
    int size() override;
    bool empty() override;
    void clear() override;
};

#endif // CACHE_VALUE_H