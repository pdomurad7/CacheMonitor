#ifndef TOPIC_MANAGER_H
#define TOPIC_MANAGER_H

#include <map>
#include <string>

class Topic;

/**
 * @brief A singleton class that manages a collection of `Topic` objects.
 * 
 * This class provides methods for creating, removing, and accessing `Topic` objects. 
 * It maintains a map of topic names to `Topic` pointers. The `getInstance` method 
 * is used to access the single instance of this class.
 */
class TopicManager {
private:
    /**
     * @brief Delete the copy constructor.
     */
    TopicManager(const TopicManager&) = delete;

    /**
     * @brief Delete the copy assignment operator.
     */
    TopicManager& operator=(const TopicManager&) = delete;

    /**
     * @brief Private constructor for the singleton class.
     */
    TopicManager() = default;

    /**
     * @brief A map of topic names to `Topic` pointers.
     */
    std::map<std::string, Topic*> topics_;

    /**
     * @brief The single instance of this class.
     */
    static TopicManager instance_;

public:
    /**
     * @brief Get the single instance of the `TopicManager` class.
     * 
     * @return A reference to the `TopicManager` instance.
     */
    static TopicManager& getInstance();

    /**
     * @brief Get a `Topic` object by name.
     * 
     * @param name The name of the topic.
     * @return A pointer to the `Topic` object, or `nullptr` if the topic does not exist.
     */
    Topic* getTopic(std::string name);

    /**
     * @brief Create a new `Topic` object.
     * 
     * @param name The name of the new topic.
     */
    void createTopic(std::string name);

    /**
     * @brief Remove a `Topic` object.
     * 
     * @param name The name of the topic to remove.
     */
    void removeTopic(std::string name);

    /**
     * @brief Change a `Topic` object's parameters.
     * 
     * @param old_topic The name of the topic to change.
     * @param new_topic The new name for the topic.
     * @param parameter The parameter to change.
     */
    void changeTopic(std::string old_topic, std::string new_topic, std::string parameter);

    /**
     * @brief Check if a `Topic` object exists.
     * 
     * @param name The name of the topic to check.
     * @return `true` if the topic exists, `false` otherwise.
     */
    bool exists(std::string name);

    /**
     * @brief Add a changed parameter to a `Topic` object.
     * 
     * @param topic The name of the topic.
     * @param parameter The parameter that has changed.
     */
    void addChangedParameter(std::string topic, std::string parameter);
};

#endif // TOPIC_MANAGER_H