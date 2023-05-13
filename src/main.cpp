#include <iostream>
#include <sw/redis++/redis++.h>
#include <redis_handler.h>
#include <topic.h>
#include <topic_manager.h>
#include <cache_value.h>

int main(){

Topic calib_data("calib_data");
Topic stero_data("stero_data");
Topic imu_data("imu_data");
CacheValue* calib_data_1 = new CacheValue("calib_data_1", &calib_data);
calib_data_1->setValue("1");
std::cout << calib_data_1->getValue() << std::endl;
calib_data_1->setValue("2");
calib_data_1->changeTopic("stero_data");
std::cout << calib_data_1->getValue() << std::endl;
for (auto i : TopicManager::getTopics()){
    std::cout << i << std::endl;
}
calib_data_1->changeTopic("imu_data");
delete calib_data_1;
}