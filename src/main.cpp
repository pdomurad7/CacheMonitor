#include <iostream>
#include <sw/redis++/redis++.h>
#include <redis_handler.h>

using namespace sw::redis;

int main(){

auto redis_handler = RedisHandler();
redis_handler.set_db(1);
auto redis1 = Redis("tcp://127.0.0.1:6379");
auto redis2 = Redis("tcp://127.0.0.1:6379");
std::cout<<redis_handler.get_db()<<std::endl;
}