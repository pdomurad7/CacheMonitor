#include <iostream>
#include <sw/redis++/redis++.h>
#include <redis_handler.h>

using namespace sw::redis;


int main(){

auto redis1 = Redis("tcp://127.0.0.1:6379");
auto redis_handler = RedisHandler(redis1);
redis1.set("key1:key2:key3","value1");
redis_handler.set_db(1);
std::cout<<redis_handler.get_db()<<std::endl;
std::vector<std::string> vec = {"a", "b", "c"};
redis1.rpush("list", "eqwe");
std::map<std::string, std::string> map;
redis1.hgetall("hash", std::inserter(map, map.end()));
redis1.hset("hash", "field", "value");
for (auto& it : map) {
    std::cout << it.first << " " << it.second << std::endl;
}
}