#include <iostream>
#include <redis_handler.h>
#include <topic_manager.h>
#include <cache_value.h>
#include <topic.h>
#include <thread>
#include <chrono>
#include <memory>

void test_creating_topic_and_value(){
    std::cout << "Testing creating topic..." << std::endl;
    TopicManager* topic_manager = TopicManager::getInstance();
    topic_manager->createTopic("test_topic");
    Topic* topic = topic_manager->getTopic("test_topic");
    // Checking if topic was created in topic manager
    if(topic == nullptr){
        std::cout << "Checking if topic was created in topic manage failed" << std::endl;
    } else {
        std::cout << "." << std::endl;
    }

    // Checking if topic was created in redis
    std::unique_ptr<AbstractCacheValue> cache_value = std::make_unique<CacheString>("test_id", "test_topic", "test_value");

    if(RedisHandler::getInstance()->exists("test_topic:test_id")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if topic with value was created in redis" << std::endl;
    }

    std::unique_ptr<AbstractCacheValue> cache_value2 = std::make_unique<CacheString>("test_id2", "test_topic");    if(RedisHandler::getInstance()->exists("test_topic:test_id2")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if topic with default value was created in redis failed" << std::endl;
    }
    // std::this_thread::sleep_for(std::chrono::seconds(10));
    // Checking if topic wad deleted in topic manager
    topic_manager->removeTopic("test_topic");
    if(topic_manager->getTopic("test_topic") != nullptr){
        std::cout << "Checking if topic wad deleted in topic manager failed" << std::endl;
    } else {
        std::cout << "." << std::endl;
    }
    // Checking if topic was deleted in redis
    if(RedisHandler::getInstance()->exists("test_topic")){
        std::cout << "Checking if topic was deleted in redis failed" << std::endl;
    } else {
        std::cout << "." << std::endl;
    }
}

void test_changing_topics(){
    std::cout << "Testing changing topics..." << std::endl;
    TopicManager::getInstance()->createTopic("test_topic");
    TopicManager::getInstance()->createTopic("test_topic2");
    // std::shared_ptr<AbstractCacheValue> cache_value = std::make_shared<CacheString>("test_id", "test_topic", "test_value");
    AbstractCacheValue* cache_value = new CacheString("test_id", "test_topic", "test_value");
    
    // Check if value is in topic 1
    if(RedisHandler::getInstance()->exists("test_topic:test_id")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if value is in topic 1 failed" << std::endl;
    }
    cache_value->changeTopic("test_topic2");

    // Check if value is in topic 2 set
    if(TopicManager::getInstance()->getTopic("test_topic2")->exists("test_value")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if value is in topic 2 set failed" << std::endl;
    }

    // Check if value is not in topic 1 set
    if(TopicManager::getInstance()->getTopic("test_topic")->exists("test_value")){
        std::cout << "Check if value is not in topic 1 set failed" << std::endl;
    } else {
        std::cout << "." << std::endl;
    }

    // Check if value is in redis topic 2
    if(RedisHandler::getInstance()->exists("test_topic2:test_id")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if value is in redis topic 2 failed" << std::endl;
    }
    
    // Check if value is not in topic 1
    if(RedisHandler::getInstance()->exists("test_topic:test_id")){
        std::cout << "Checking if value is not in topic 1 failed" << std::endl;
    } else {
        std::cout << "." << std::endl;
    }
}


int main(){
    test_creating_topic_and_value();
    test_changing_topics();
}