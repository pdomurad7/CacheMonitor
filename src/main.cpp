#include <iostream>
#include <redis_handler.h>
#include <topic_manager.h>
#include <cache_value.h>
#include <topic.h>
#include <thread>
#include <chrono>
#include <memory>
#include <sstream>
#include <gtest/gtest.h>

TEST(TestCacheValue, CheckCacheString)
{
    TopicManager::getInstance().createTopic("test_topic");
    auto cache_value = std::make_shared<CacheString>("test_id", "test_topic", "test_value");
    ASSERT_EQ("test_value", cache_value->toString()) << "CacheString value is not correct";

    cache_value->setValue("new_value");
    ASSERT_EQ("new_value", cache_value->toString()) << "CacheString value after set is not correct";
}

TEST(TestCacheValue, CheckCacheInt)
{
    TopicManager::getInstance().createTopic("test_topic");
    auto cache_value = std::make_shared<CacheInt>("test_id", "test_topic", 123);
    ASSERT_EQ(123, cache_value->toInt()) << "CacheInt value is not correct";

    cache_value->setValue(456);
    ASSERT_EQ(456, cache_value->toInt()) << "CacheInt value after set is not correct";
}

TEST(TestCacheValue, CheckCacheFloat)
{
    TopicManager::getInstance().createTopic("test_topic");
    auto cache_value = std::make_shared<CacheFloat>("test_id", "test_topic", 123.45f);
    ASSERT_FLOAT_EQ(123.45f, cache_value->toFloat()) << "CacheFloat value is not correct";

    cache_value->setValue(456.78f);
    ASSERT_FLOAT_EQ(456.78f, cache_value->toFloat()) << "CacheFloat value after set is not correct";
}

TEST(TestTopic, CreatingAndDeletingTopic)
{
    TopicManager::getInstance().createTopic("test_topic");
    Topic *topic = TopicManager::getInstance().getTopic("test_topic");
    ASSERT_FALSE(topic == nullptr) << "Topic was not created in topic manager";

    std::unique_ptr<AbstractCacheValue> cache_value = std::make_unique<CacheString>("test_id", "test_topic", "test_value");
    ASSERT_TRUE(RedisHandler::getInstance().getRedis()->exists("test_topic:test_id")) << "Topic was not created in redis";

    std::unique_ptr<AbstractCacheValue> cache_value2 = std::make_unique<CacheString>("test_id2", "test_topic");
    ASSERT_TRUE(RedisHandler::getInstance().getRedis()->exists("test_topic:test_id2")) << "Topic with default value was not created in redis";

    TopicManager::getInstance().removeTopic("test_topic");
    ASSERT_FALSE(TopicManager::getInstance().getTopic("test_topic")) << "Topic was not deleted in topic manager";
    ASSERT_FALSE(RedisHandler::getInstance().getRedis()->exists("test_topic")) << "Topic was not deleted in redis";
}

TEST(TestTopic, ChangingTopics)
{
    TopicManager::getInstance().createTopic("first_topic");
    TopicManager::getInstance().createTopic("second_topic");
    std::shared_ptr<AbstractCacheValue> cache_value = std::make_shared<CacheString>("test_id", "first_topic", "test_value");
    ASSERT_TRUE(RedisHandler::getInstance().getRedis()->exists("first_topic:test_id")) << "Value is not in first topic";

    cache_value->changeTopic("second_topic");
    ASSERT_TRUE(TopicManager::getInstance().getTopic("second_topic")->exists("test_id")) << "Value is not in second topic set";
    ASSERT_FALSE(TopicManager::getInstance().getTopic("first_topic")->exists("test_id")) << "Value is still in first topic set";
    ASSERT_TRUE(RedisHandler::getInstance().getRedis()->exists("second_topic:test_id")) << "Value is not in redis second topic";
    ASSERT_FALSE(RedisHandler::getInstance().getRedis()->exists("first_topic:test_id")) << "Value is still in redis first topic";
}

TEST(TestRedisCallback, CheckChangedParameters)
{
    TopicManager::getInstance().createTopic("changed_parameters_topic");
    ASSERT_EQ(0, TopicManager::getInstance().getTopic("changed_parameters_topic")->check_changed_parameters().size()) << "Changed parameters topic is not empty";

    std::shared_ptr<AbstractCacheValue> cache_value = std::make_shared<CacheString>("test_id", "changed_parameters_topic", "test_value");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ(1, TopicManager::getInstance().getTopic("changed_parameters_topic")->check_changed_parameters().size()) << "Changed parameters topic does not have one parameter";
    ASSERT_TRUE(TopicManager::getInstance().getTopic("changed_parameters_topic")->check_changed_parameters().contains("test_id")) << "Changed parameters topic does not have correct parameter";
}

TEST(TestRedisCallback, CheckGetValue)
{
    TopicManager::getInstance().createTopic("get_value_topic");
    std::shared_ptr<AbstractCacheValue> cache_value = std::make_shared<CacheString>("test_id", "get_value_topic", "test_value");
    RedisHandler::getInstance().getRedis()->set("get_value_topic:test_id", "another_value");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_EQ("another_value", TopicManager::getInstance().getTopic("get_value_topic")->getCacheValue("test_id")->toString()) << "Get value is not correct";
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}