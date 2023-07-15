#ifndef CACHE_VALUE_H
#define CACHE_VALUE_H

#include <string>
#include <any>

#include <redis_handler.h>

class Topic;

/**
 * @brief Abstract base class for cache values.
 * 
 * Base cache value class, which provides common interface for manipulating cache values, like
 * getting their values, adding values to redis or changing topic. This functionalities are needed
 * in class like Topic or TopicManager.
 */
class AbstractCacheValue{
protected:
    /**
     * @brief The ID of the cache value.
     */
    std::string id_;

    /**
     * @brief Pointer to the Topic associated with this cache value.
     */
    Topic* topic_;

    /**
     * @brief Remove the value from Redis.
     */
    void removeValueFromRedis_();

    /**
     * @brief Abstract method to add the value to Redis, to be implemented by derived classes.
     */
    virtual void addValueToRedis_() = 0;

public:
    /**
     * @brief Construct a new Abstract Cache Value object.
     * 
     * @param id The ID of the cache value.
     * @param topic The topic of the cache value.
     */
    AbstractCacheValue(std::string id, std::string topic);

    /**
     * @brief Destroy the Abstract Cache Value object.
     */
    virtual ~AbstractCacheValue() = default;

    /**
     * @brief Get the ID of the cache value.
     * 
     * @return The ID of the cache value as a string.
     */
    std::string getId();

    /**
     * @brief Get the Topic object associated with the cache value.
     * 
     * @return Pointer to the Topic object.
     */
    Topic* getTopic();

    /**
     * @brief Change the topic of the cache value. Which also means changin value path in redis.
     * 
     * @param topic The new topic.
     */
    void changeTopic(std::string topic);

    /**
     * @brief Convert the std::any value of the cache to a string.
     * 
     * @return The cache value as a string.
     */
    std::string toString();

    /**
     * @brief Convert the std::any value of the cache to an integer.
     * 
     * @return The cache value as an integer.
     */
    int toInt();

    /**
     * @brief Convert the std::any value of the cache to a float.
     * 
     * @return The cache value as a float.
     */
    float toFloat();

    /**
     * @brief Convert the std::any value of the cache to a list of strings.
     * 
     * @return The cache value as a list of strings.
     */
    std::list<std::string> toList();

    /**
     * @brief Convert the std::any value of the cache to a map from strings to strings.
     * 
     * @return The cache value as a map from strings to strings.
     */
    std::map<std::string, std::string> toMap();

    /**
     * @brief Convert the std::any value of the cache to a set of strings.
     * 
     * @return The cache value as a set of strings.
     */
    std::set<std::string> toSet();

    /**
     * @brief Get the value of the cache. To be implemented by derived classes.
     * Implementation depends on retrieving value from Redis and converting to propar value type.
     * Every time this method is called, we are checking if value in redis has changed. If so, we
     * update and returns new value.
     * 
     * @return The value of the cache as a std::any object.
     */
    virtual std::any getValue() = 0;
};
/**
 * @brief A cache value that contains a string.
 * 
 * This class inherits from the `AbstractCacheValue` base class and encapsulates a string value. It provides an 
 * implementation of the `getValue` method, which retrieves the string value as a `std::any` object, and the 
 * `setValue` method, which sets the string value. The `addValueToRedis_` method, which is used to add the 
 * value to a Redis database, is also overridden in this class.
 */
class CacheString : public AbstractCacheValue{
    /**
     * @brief The string value stored in the cache.
     */
    std::string value_;

    /**
     * @brief Add the string value to a Redis database.
     * 
     * This method is overridden from the `AbstractCacheValue` base class.
     */
    void addValueToRedis_() override;

public:
    /**
     * @brief Construct a new `CacheString` object.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class with the given parameters
     * and setting default value which is empty string.
     *  
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     */
    CacheString(std::string id, std::string topic_path);

    /**
     * @brief Construct a new `CacheString` object with an initial value.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class and the `value_` member
     * of this class with the given parameters.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     * @param value The initial string value.
     */
    CacheString(std::string id, std::string topic_path, std::string value);

    /**
     * @brief Destroy the `CacheString` object.
     */
    ~CacheString()=default;

    /**
     * @brief Get the string value of the cache.
     * 
     * This method is overridden from the `AbstractCacheValue` base class.
     * 
     * @return The string value of the cache as a `std::any` object.
     */
    std::any getValue() override;

    /**
     * @brief Set the string value of the cache.
     * 
     * This method sets the `value_` member of this class to the given string value and
     * updates the value in the Redis database.
     * 
     * @param value The new string value.
     */
    void setValue(std::string value);
};

/**
 * @brief A cache value that contains an integer.
 * 
 * This class inherits from the `AbstractCacheValue` base class and encapsulates an integer value. It provides an 
 * implementation of the `getValue` method, which retrieves the integer value as a `std::any` object, and the 
 * `setValue` method, which sets the integer value. The `addValueToRedis_` method, which is used to add the 
 * value to a Redis database, is also overridden in this class.
 */
class CacheInt : public AbstractCacheValue {
    /**
     * @brief The integer value stored in the cache.
     */
    int value_;

    /**
     * @brief Add the integer value to a Redis database.
     * 
     * This method is overridden from the `AbstractCacheValue` base class.
     */
    void addValueToRedis_() override;

public:
    /**
     * @brief Construct a new `CacheInt` object.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class with the given parameters
     * and sets default value which is 0.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     */
    CacheInt(std::string id, std::string topic_path);

    /**
     * @brief Construct a new `CacheInt` object with an initial value.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class and the `value_` member
     * of this class with the given parameters.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     * @param value The initial integer value.
     */
    CacheInt(std::string id, std::string topic_path, int value);

    /**
     * @brief Destroy the `CacheInt` object.
     */
    ~CacheInt() = default;

    /**
     * @brief Get the integer value of the cache.
     * 
     * This method is overridden from the `AbstractCacheValue` base class.
     * 
     * @return The integer value of the cache as a `std::any` object.
     */
    std::any getValue() override;

    /**
     * @brief Set the integer value of the cache.
     * 
     * This method sets the `value_` member of this class to the given integer value and
     * updates the value in the Redis.
     * 
     * @param value The new integer value.
     */
    void setValue(int value);
};
/**
 * @brief A cache value that contains a float.
 * 
 * This class inherits from the `AbstractCacheValue` base class and encapsulates a float value. It provides an 
 * implementation of the `getValue` method, which retrieves the float value as a `std::any` object, and the 
 * `setValue` method, which sets the float value. The `addValueToRedis_` method, which is used to add the 
 * value to a Redis database, is also overridden in this class.
 */
class CacheFloat : public AbstractCacheValue {
    /**
     * @brief The float value stored in the cache.
     */
    float value_;

    /**
     * @brief Add the float value to a Redis database.
     * 
     * This method is overridden from the `AbstractCacheValue` base class.
     */
    void addValueToRedis_() override;

public:
    /**
     * @brief Construct a new `CacheFloat` object.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class with the given parameters
     * and sets default value which is 0.0.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     */
    CacheFloat(std::string id, std::string topic_path);

    /**
     * @brief Construct a new `CacheFloat` object with an initial value.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class and the `value_` member
     * of this class with the given parameters.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     * @param value The initial float value.
     */
    CacheFloat(std::string id, std::string topic_path, float value);

    /**
     * @brief Destroy the `CacheFloat` object.
     */
    ~CacheFloat() = default;

    /**
     * @brief Get the float value of the cache.
     * 
     * This method is overridden from the `AbstractCacheValue` base class.
     * 
     * @return The float value of the cache as a `std::any` object.
     */
    std::any getValue() override;

    /**
     * @brief Set the float value of the cache.
     * 
     * This method sets the `value_` member of this class to the given float value and
     * updates the value in the Redis.
     * 
     * @param value The new float value.
     */
    void setValue(float value);
};

/**
 * @brief An abstract cache value that contains a container.
 * 
 * This class inherits from the `AbstractCacheValue` base class and serves as the base class for cache values that
 * contain containers such as lists, maps, or sets. It declares several pure virtual functions that must be 
 * implemented by the derived classes: `clear`, `size`, `contains`, and `empty`.
 */
class ContainerCacheValue : public AbstractCacheValue{
public:
    /**
     * @brief Construct a new `ContainerCacheValue` object.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class with the given parameters.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     */
    ContainerCacheValue(std::string id, std::string topic_path);

    /**
     * @brief Destroy the `ContainerCacheValue` object.
     */
    virtual ~ContainerCacheValue() = default;

    /**
     * @brief Clear the container.
     * 
     * This method clears the container and deletes temporary value from Redis.
     * This is a pure virtual function that must be implemented by the derived classes.
     */
    virtual void clear() = 0;

    /**
     * @brief Get the size of the container.
     * 
     * This is a pure virtual function that must be implemented by the derived classes.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return The size of the container.
     */
    virtual int size() = 0;

    /**
     * @brief Check if the container contains a certain value.
     * 
     * This is a pure virtual function that must be implemented by the derived classes.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @param value The value to check for.
     * @return `true` if the container contains the value, `false` otherwise.
     */
    virtual bool contains(std::string value) = 0;

    /**
     * @brief Check if the container is empty.
     * 
     * This is a pure virtual function that must be implemented by the derived classes.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return `true` if the container is empty, `false` otherwise.
     */
    virtual bool empty() = 0;
};

/**
 * @brief A cache value that contains a list of strings.
 * 
 * This class inherits from the `ContainerCacheValue` base class and encapsulates a list of strings. It provides an 
 * implementation of the `getValue`, `setValue`, `size`, `contains`, `empty`, and `clear` methods. The `addValueToRedis_` 
 * method, which is used to add the list to a Redis database, is also overridden in this class. Additional methods for 
 * manipulating the list (`rpush`, `lpush`, `rpop`, `lpop`) are also provided.
 */
class CacheList : public ContainerCacheValue{
    /**
     * @brief The list of strings stored in the cache.
     */
    std::list<std::string> value_;

    /**
     * @brief Add the list of strings to a Redis database.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     */
    void addValueToRedis_() override;

public:
    /**
     * @brief Construct a new `CacheList` object with an initial list.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class and the `value_` member
     * of this class with the given parameters.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     * @param value The initial list of strings.
     */
    CacheList(std::string id, std::string topic_path, std::list<std::string> value);

    /**
     * @brief Destroy the `CacheList` object.
     */
    ~CacheList() = default;

    /**
     * @brief Get the list of strings from the cache.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns new value.
     * 
     * @return The list of strings from the cache as a `std::any` object.
     */
    std::any getValue() override;

    /**
     * @brief Set the list of strings in the cache.
     * 
     * This method sets the `value_` member of this class to the given list of strings and
     * updates the list in the Redis.
     * 
     * @param value The new list of strings.
     */
    void setValue(std::list<std::string> value);

    /**
     * @brief Add a string to the end of the list.
     * 
     * This method adds a string to the end of the `value_` list.
     * Updates value in Redis.
     * 
     * @param value The string to add.
     */
    void rpush(std::string value);

    /**
     * @brief Add a string to the front of the list.
     * 
     * This method adds a string to the front of the `value_` list.
     * Updates value in Redis.
     * 
     * @param value The string to add.
     */
    void lpush(std::string value);

    /**
     * @brief Remove and return a string from the end of the list.
     * 
     * This method removes a string from the end of the `value_` list and returns it.
     * Updates value in Redis.
     * 
     * @return The removed string.
     */
    std::string rpop();

    /**
     * @brief Remove and return a string from the front of the list.
     * 
     * This method removes a string from the front of the `value_` list and returns it.
     * Updates value in Redis.
     * 
     * @return The removed string.
     */
    std::string lpop();

    /**
     * @brief Get the size of the list.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return The size of the list.
     */
    int size() override;

    /**
     * @brief Check if the list contains a certain string.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @param value The string to check for.
     * @return `true` if the list contains the string, `false` otherwise.
     */
    bool contains(std::string value) override;

    /**
     * @brief Check if the list is empty.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return `true` if the list is empty, `false` otherwise.
     */
    bool empty() override;

    /**
     * @brief Clear the list.
     * 
     * This method is overridden from the `ContainerCacheValue` base class. It clears the `value_` list and
     * removes the list from the Redis.
     */
    void clear() override;
};

/**
 * @brief A cache value that contains a map of strings to strings.
 * 
 * This class inherits from the `ContainerCacheValue` base class and encapsulates a map of strings. It provides an 
 * implementation of the `getValue`, `setValue`, `size`, `contains`, `empty`, and `clear` methods. The `addValueToRedis_` 
 * method, which is used to add the map to a Redis database, is also overridden in this class. Additional methods for 
 * manipulating the map (`addKey`, `eraseKey`, `getKey`) are also provided.
 */
class CacheMap : public ContainerCacheValue{
    /**
     * @brief The map of strings stored in the cache.
     */
    std::map<std::string, std::string> value_;

    /**
     * @brief Add the map of strings to a Redis database.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     */
    void addValueToRedis_() override;

public:
    /**
     * @brief Construct a new `CacheMap` object with an initial map.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class and the `value_` member
     * of this class with the given parameters.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     * @param value The initial map of strings.
     */
    CacheMap(std::string id, std::string topic_path, std::map<std::string, std::string> value);

    /**
     * @brief Destroy the `CacheMap` object.
     */
    ~CacheMap() = default;

    /**
     * @brief Get the map of strings from the cache.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns new value.
     * 
     * @return The map of strings from the cache as a `std::any` object.
     */
    std::any getValue() override;

    /**
     * @brief Set the map of strings in the cache.
     * 
     * This method sets the `value_` member of this class to the given map of strings and
     * updates the map in the Redis.
     * 
     * @param value The new map of strings.
     */
    void setValue(std::map<std::string, std::string> value);

    /**
     * @brief Add a key-value pair to the map.
     * 
     * This method adds a key-value pair to the `value_` map.
     * Updates value in Redis.
     * 
     * @param key The key to add.
     * @param value The value to add.
     */
    void addKey(std::string key, std::string value);

    /**
     * @brief Erase a key-value pair from the map.
     * 
     * This method erases a key-value pair from the `value_` map using the key.
     * Updates value in Redis.
     * 
     * @param key The key of the key-value pair to erase.
     */
    void eraseKey(std::string key);

    /**
     * @brief Get the value associated with a key in the map.
     * 
     * This method chekc if value changed
     * and returns the value associated with a key in the `value_` map.
     * If key does not exist, throw std::invalid_argument.
     * 
     * @param key The key to search for.
     * @return The value associated with the key.
     */
    std::string getKey(std::string key);

    /**
     * @brief Get the size of the map.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return The size of the map.
     */
    int size() override;

    /**
     * @brief Check if the map contains a certain key.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @param key The key to check for.
     * @return `true` if the map contains the key, `false` otherwise.
     */
    bool contains(std::string key) override;

    /**
     * @brief Check if the map is empty.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return `true` if the map is empty, `false` otherwise.
     */
    bool empty() override;

    /**
     * @brief Clear the map.
     * 
     * This method is overridden from the `ContainerCacheValue` base class. It clears the `value_` map and
     * removes the map from the Redis.
     */
    void clear() override;
};

/**
 * @brief A cache value that contains a set of strings.
 * 
 * This class inherits from the `ContainerCacheValue` base class and encapsulates a set of strings. It provides an 
 * implementation of the `getValue`, `setValue`, `size`, `contains`, `empty`, and `clear` methods. The `addValueToRedis_` 
 * method, which is used to add the set to a Redis database, is also overridden in this class. Additional methods for 
 * manipulating the set (`addValue`, `removeValue`) are also provided.
 */
class CacheSet : public ContainerCacheValue {
private:
    /**
     * @brief The set of strings stored in the cache.
     */
    std::set<std::string> value_;

    /**
     * @brief Add the set of strings to a Redis database.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     */
    void addValueToRedis_() override;

public:
    /**
     * @brief Construct a new `CacheSet` object with an initial set.
     * 
     * This constructor initializes the `id_` and `topic_` members of the base class and the `value_` member
     * of this class with the given parameters.
     * 
     * @param id The ID of the cache value.
     * @param topic_path The topic path of the cache value.
     * @param value The initial set of strings.
     */
    CacheSet(std::string id, std::string topic_path, std::set<std::string> value);

    /**
     * @brief Destroy the `CacheSet` object.
     */
    ~CacheSet() = default;

    /**
     * @brief Get the set of strings from the cache.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns new value.
     * 
     * @return The set of strings from the cache as a `std::any` object.
     */
    std::any getValue() override;

    /**
     * @brief Set the set of strings in the cache.
     * 
     * This method sets the `value_` member of this class to the given set of strings and
     * updates the set in the Redis.
     * 
     * @param value The new set of strings.
     */
    void setValue(std::set<std::string> value);

    /**
     * @brief Add a string to the set.
     * 
     * This method adds a string to the `value_` set.
     * Updates value in Redis.
     * 
     * @param val The string to add.
     */
    void addValue(std::string val);

    /**
     * @brief Remove a string from the set.
     * 
     * This method removes a string from the `value_` set.
     * Updates value in Redis.
     * 
     * @param val The string to remove.
     */
    void removeValue(std::string val);

    /**
     * @brief Check if the set contains a certain string.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @param val The string to check for.
     * @return `true` if the set contains the string, `false` otherwise.
     */
    bool contains(std::string val) override;

    /**
     * @brief Get the size of the set.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return The size of the set.
     */
    int size() override;

    /**
     * @brief Check if the set is empty.
     * 
     * This method is overridden from the `ContainerCacheValue` base class.
     * Checks if value in redis has changed. If so, we update and returns up to date result.
     * 
     * @return `true` if the set is empty, `false` otherwise.
     */
    bool empty() override;

    /**
     * @brief Clear the set.
     * 
     * This method is overridden from the `ContainerCacheValue` base class. It clears the `value_` set and
     * removes the set from the Redis.
     */
    void clear() override;
};

#endif // CACHE_VALUE_H