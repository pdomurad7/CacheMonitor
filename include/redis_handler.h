#ifndef REDIS_HANDLER_H
#define REDIS_HANDLER_H

#include <sw/redis++/redis++.h>
#include <map>
#include <set>
#include <memory>
#include <thread>
#include <atomic>

/**
 * @brief A singleton class that manages a connection to a Redis database.
 * 
 * This class encapsulates a connection to a Redis database using the `sw::redis::Redis` class. 
 * It also maintains a subscriber for the Redis publish/subscribe mechanism, and runs a worker 
 * thread that processes incoming messages from subscribed Redis channels and check if value changed, if so add value id to 
 * changed paramaters set in value topic.
 * The `getInstance` method is used to access the single instance of this class.
 */
class RedisHandler {
private:
    /**
     * @brief The single instance of this class.
     */
    static RedisHandler instance_;

    /**
     * @brief A shared pointer to the Redis object.
     */
    std::shared_ptr<sw::redis::Redis> redis_;

    /**
     * @brief The Redis subscriber object.
     */
    sw::redis::Subscriber sub_;

    /**
     * @brief Atomic boolean flag to control the worker thread.
     */
    std::atomic<bool> stop_worker_;

    /**
     * @brief The Redis connection options.
     */
    sw::redis::ConnectionOptions connection_options_();

    /**
     * @brief The worker thread.
     */
    std::thread worker_thread_;

    /**
     * @brief The worker function that runs in `worker_thread_`. Consuming messages from Redis channels every interval time and check if value changed,
     * if so add value id to changed paramaters set in value topic.
     */
    void worker_(sw::redis::Subscriber&, int, const std::atomic<bool>&);

    /**
     * @brief Private constructor for the singleton class.
     */
    RedisHandler();

public:
    /**
     * @brief Destructor for the singleton class.
     */
    ~RedisHandler();

    /**
     * @brief Delete the copy constructor.
     */
    RedisHandler(const RedisHandler&) = delete;

    /**
     * @brief Delete the copy assignment operator.
     */
    RedisHandler& operator=(const RedisHandler&) = delete;

    /**
     * @brief Get the single instance of the `RedisHandler` class.
     * 
     * @return A reference to the `RedisHandler` instance.
     */
    static RedisHandler& getInstance();

    /**
     * @brief Get the Redis connection object.
     * 
     * @return A pointer to the `sw::redis::Redis` object.
     */
    sw::redis::Redis* getRedis();
};

#endif // REDIS_HANDLER_H
