#include <redis_handler.h>

void RedisHandler::set_db(int db) {
    db_ = db;
}
int RedisHandler::get_db() {
    return db_;
}