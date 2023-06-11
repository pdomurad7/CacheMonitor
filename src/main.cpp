#include <iostream>
#include <redis_handler.h>
#include <topic_manager.h>
#include <cache_value.h>
#include <topic.h>
#include <thread>
#include <chrono>
#include <memory>
#include <sstream>

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
    TopicManager::getInstance()->createTopic("first_topic");
    TopicManager::getInstance()->createTopic("second_topic");
    std::shared_ptr<AbstractCacheValue> cache_value = std::make_shared<CacheString>("test_id", "first_topic", "test_value");
    
    // Check if value is in first topic
    if(RedisHandler::getInstance()->exists("first_topic:test_id")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if value is in first topic failed" << std::endl;
    }
    cache_value->changeTopic("second_topic");

    // Check if value is in second topic set
    if(TopicManager::getInstance()->getTopic("second_topic")->exists("test_id")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if value is in second topic set failed" << std::endl;
    }

    // Check if value is not in first topic set
    if(TopicManager::getInstance()->getTopic("first_topic")->exists("test_id")){
        std::cout << "Check if value is not in first topic set failed" << std::endl;
    } else {
        std::cout << "." << std::endl;
    }

    // Check if value is in redis second topic
    if(RedisHandler::getInstance()->exists("second_topic:test_id")){
        std::cout << "." << std::endl;
    } else {
        std::cout << "Checking if value is in redis second topic failed" << std::endl;
    }
    
    // Check if value is not in first topic
    if(RedisHandler::getInstance()->exists("first_topic:test_id")){
        std::cout << "Checking if value is not in first topic failed" << std::endl;
    } else {
        std::cout << "." << std::endl;
    }
}


int main(){
    test_creating_topic_and_value();
    test_changing_topics();

//     TopicManager::getInstance()->createTopic("first_topic");
//     TopicManager::getInstance()->createTopic("second_topic");
//     TopicManager::getInstance()->createTopic("third_topic");
//     std::shared_ptr<AbstractCacheValue> cache_value = std::make_shared<CacheString>("first_id_first_topic", "first_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value2 = std::make_shared<CacheString>("second_id_first_topic", "first_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value3 = std::make_shared<CacheString>("third_id_first_topic", "first_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value4 = std::make_shared<CacheString>("first_id_second_topic", "second_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value5 = std::make_shared<CacheString>("second_id_second_topic", "second_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value6 = std::make_shared<CacheString>("third_id_second_topic", "second_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value7 = std::make_shared<CacheString>("first_id_third_topic", "third_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value8 = std::make_shared<CacheString>("second_id_third_topic", "third_topic", "test_value");
//     std::shared_ptr<AbstractCacheValue> cache_value9 = std::make_shared<CacheString>("third_id_third_topic", "third_topic", "test_value");


//     RedisHandler::getInstance()->command("config", "set", "notify-keyspace-events", "KEA");
//     auto sub = RedisHandler::getInstance()->subscriber();
//     sub.psubscribe("__keyspace@0__:*");
//     sub.on_pmessage([](std::string pattern, std::string channel, std::string msg) {
//         std::istringstream msgstream(channel);
//         std::getline(msgstream, channel, ':');
//         std::string topic_path;
//         std::string value_id;

//         std::getline(msgstream, topic_path, ':');
//         std::getline(msgstream, value_id, ':');

//         TopicManager::getInstance()->addChangedParameter(topic_path, value_id);
//     });


//     auto counter = 0;

//     while (counter < 5) {
//         sub.consume();
//         std::cout<<counter<<std::endl;
//         counter++;
//         // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
// }

//     for(auto p : TopicManager::getInstance()->getTopic("first_topic")->check_changed_parameters()){
//         std::cout<<p<<std::endl;
//     }

//     for (auto p : TopicManager::getInstance()->getTopic("second_topic")->check_changed_parameters()){
//         std::cout<<p<<std::endl;
//     }

//     for (auto p : TopicManager::getInstance()->getTopic("third_topic")->check_changed_parameters()){
//         std::cout<<p<<std::endl;
//     }

}