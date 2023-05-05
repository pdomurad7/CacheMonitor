#include <sw/redis++/redis++.h>

class RedisHandler {
    int db_;
    sw::redis::Redis* redis_;
public:
    RedisHandler(sw::redis::Redis &redis);
    void set_db(int db);
    int get_db();
};