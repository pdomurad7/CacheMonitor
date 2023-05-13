#ifndef TOPIC_H
#define TOPIC_H

#include <set>
#include <sw/redis++/redis++.h>
class Topic{
    std::set<std::string> chagned_parameters_;
    std::string topic_path_;
public:
    Topic(std::string topic_path);
    ~Topic();
    Topic(const Topic& other) = delete;
    Topic& operator=(const Topic& other) = delete;
    std::string getTopicPath();
};

#endif // TOPIC_H