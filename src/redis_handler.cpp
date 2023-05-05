#include <redis_handler.h>
#include <sw/redis++/redis++.h>

RedisHandler::RedisHandler(sw::redis::Redis &redis) {
    redis_ = &redis;
}

void RedisHandler::set_db(int db) {
    db_ = db;
}
int RedisHandler::get_db() {
    return db_;
}
