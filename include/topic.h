#ifndef TOPIC_H
#define TOPIC_H

#include <set>
#include <map>

#include <topic_manager.h>

class AbstractCacheValue;

/**
 * @brief A class that represents a topic in the cache.
 * 
 * This class maintains a set of parameters that have changed (`changed_parameters_`), 
 * a map of cache values (`cache_values_`), and the path of the topic (`topic_path_`).
 * Topic path is path where values from this topic are stored in redis. 
 * It provides methods for checking and clearing changed parameters, adding, removing, 
 * and accessing cache values, and checking if a cache value exists. It also provides 
 * methods for managing the topic path.
 */
class Topic {
private:
    /**
     * @brief A set of parameters that have changed.
     */
    std::set<std::string> changed_parameters_;

    /**
     * @brief The path of the topic.
     */
    std::string topic_path_;

    /**
     * @brief A map of cache values.
     * 
     * The keys are the IDs of the cache values and the values are pointers to `AbstractCacheValue` objects.
     */
    std::map <std::string, AbstractCacheValue*> cache_values_;

    /**
     * @brief Construct a new `Topic` object.
     * 
     * @param topic_path The path of the topic.
     */
    Topic(std::string topic_path);

    /**
     * @brief Destroy the `Topic` object.
     */
    ~Topic() = default;

    /**
     * @brief Give the `TopicManager` class friend access.
     * 
     * This allows the `TopicManager` class to access the private members and methods of this class.
     */
    friend class TopicManager;

public:
    /**
     * @brief Delete the copy constructor.
     */
    Topic(const Topic& other) = delete;

    /**
     * @brief Delete the copy assignment operator.
     */
    Topic& operator=(const Topic& other) = delete;

    /**
     * @brief Check the parameters that have changed.
     * 
     * @return A set of the parameters that have changed.
     */
    std::set<std::string> check_changed_parameters();

    /**
     * @brief Clear the set of changed parameters.
     */
    void clear_changed_parameters();

    /**
     * @brief Remove a changed parameter.
     * 
     * @param parameter The parameter to remove.
     */
    void removeChangedParameter(std::string parameter);

    /**
     * @brief Get the path of the topic.
     * 
     * @return The path of the topic.
     */
    std::string getTopicPath();

    /**
     * @brief Add a cache value to the topic.
     * 
     * @param cache_value A pointer to the `AbstractCacheValue` object to add.
     */
    void addCacheValue(AbstractCacheValue* cache_value);

    /**
     * @brief Remove a cache value from the topic.
     * 
     * @param id The ID of the cache value to remove.
     */
    void removeCacheValue(std::string id);

    /**
     * @brief Get a cache value from the topic.
     * 
     * @param id The ID of the cache value to get.
     * @return A pointer to the `AbstractCacheValue` object, or `nullptr` if the cache value does not exist.
     */
    AbstractCacheValue* getCacheValue(std::string id);

    /**
     * @brief Check if a cache value exists.
     * 
     * @param id The ID of the cache value to check.
     * @return `true` if the cache value exists, `false` otherwise.
     */
    bool exists(std::string id);
};

#endif // TOPIC_H