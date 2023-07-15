#include <cache_value.h>
#include <topic_manager.h>
#include <topic.h>
#include <iostream>

AbstractCacheValue::AbstractCacheValue(std::string id, std::string topic_path){
    id_ = id;
    topic_ = TopicManager::getInstance().getTopic(topic_path);
}

std::string AbstractCacheValue::getId(){
    return id_;
}

void AbstractCacheValue::setId(std::string id){
    id_ = id;
}

Topic* AbstractCacheValue::getTopic(){
    return topic_;
}

void AbstractCacheValue::changeTopic(std::string new_topic_path){
    // TODO: handling changing on non existing topic
    std::string old_topic_path = topic_->getTopicPath();
    removeValueFromRedis_();
    topic_ = TopicManager::getInstance().getTopic(new_topic_path);
    TopicManager::getInstance().changeTopic(id_, old_topic_path, new_topic_path);
    addValueToRedis_();
}

std::string AbstractCacheValue::toString(){
    return std::any_cast<std::string>(getValue());
}

int AbstractCacheValue::toInt(){
    return std::any_cast<int>(getValue());
}

float AbstractCacheValue::toFloat(){
    return std::any_cast<float>(getValue());
}

std::list<std::string> AbstractCacheValue::toList(){
    return std::any_cast<std::list<std::string>>(getValue());
}

std::map<std::string, std::string> AbstractCacheValue::toMap(){
    return std::any_cast<std::map<std::string, std::string>>(getValue());
}

std::set<std::string> AbstractCacheValue::toSet(){
    return std::any_cast<std::set<std::string>>(getValue());
}

void AbstractCacheValue::removeValueFromRedis_(){
    RedisHandler::getInstance().getRedis()->del(topic_->getTopicPath() + ":" + id_);
}

CacheString::CacheString(std::string id, std::string topic_path) : AbstractCacheValue(id, topic_path){
    // TODO same as in another constructor
    value_ = "";
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

CacheString::CacheString(std::string id, std::string topic_path, std::string value) : AbstractCacheValue(id, topic_path){
    value_ = value;
    // TODO check if topic exists
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

std::any CacheString::getValue() {
    if (topic_->check_changed_parameters().contains(id_)) {
        value_ = *RedisHandler::getInstance().getRedis()->get(topic_->getTopicPath() + ":" + id_);
        topic_->removeChangedParameter(id_);
    }
    return value_;
}

void CacheString::setValue(std::string value){
    value_ = value;
    addValueToRedis_();
}

void CacheString::addValueToRedis_(){
    RedisHandler::getInstance().getRedis()->set(topic_->getTopicPath() + ":" + id_, value_);
}


CacheInt::CacheInt(std::string id, std::string topic_path) : AbstractCacheValue(id, topic_path){
    value_ = 0;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

CacheInt::CacheInt(std::string id, std::string topic_path, int value) : AbstractCacheValue(id, topic_path){
    value_ = value;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

std::any CacheInt::getValue() {
    if (topic_->check_changed_parameters().contains(id_)) {
        value_ = std::stoi(*RedisHandler::getInstance().getRedis()->get(topic_->getTopicPath() + ":" + id_));
        topic_->removeChangedParameter(id_);
    }
    return value_;
}

void CacheInt::setValue(int value){
    value_ = value;
    addValueToRedis_();
}

void CacheInt::addValueToRedis_(){
    RedisHandler::getInstance().getRedis()->set(topic_->getTopicPath() + ":" + id_, std::to_string(value_));
}

CacheFloat::CacheFloat(std::string id, std::string topic_path) : AbstractCacheValue(id, topic_path){
    value_ = 0.0f;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

CacheFloat::CacheFloat(std::string id, std::string topic_path, float value) : AbstractCacheValue(id, topic_path){
    value_ = value;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

std::any CacheFloat::getValue() {
    if (topic_->check_changed_parameters().contains(id_)) {
        value_ = std::stof(*RedisHandler::getInstance().getRedis()->get(topic_->getTopicPath() + ":" + id_));
        topic_->removeChangedParameter(id_);
    }
    return value_;
}

void CacheFloat::setValue(float value){
    value_ = value;
    addValueToRedis_();
}

void CacheFloat::addValueToRedis_(){
    RedisHandler::getInstance().getRedis()->set(topic_->getTopicPath() + ":" + id_, std::to_string(value_));
}

ContainerCacheValue::ContainerCacheValue(std::string id, std::string topic_path) : AbstractCacheValue(id, topic_path){};

CacheList::CacheList(std::string id, std::string topic_path, std::list<std::string> value) : ContainerCacheValue(id, topic_path){
    value_ = value;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

void CacheList::addValueToRedis_(){
    RedisHandler::getInstance().getRedis()->rpush(topic_->getTopicPath() + ":" + id_, value_.begin(), value_.end());
}

void CacheList::setValue(std::list<std::string> value){
    value_ = value;
    addValueToRedis_();
}

std::any CacheList::getValue(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->lrange(topic_->getTopicPath() + ":" + id_, 0, -1, std::back_inserter(value_));
        topic_->removeChangedParameter(id_);
    }
    return value_;
}

void CacheList::rpush(std::string value){
    RedisHandler::getInstance().getRedis()->rpush(topic_->getTopicPath() + ":" + id_, value);
}

std::string CacheList::rpop(){
    std::string value = *RedisHandler::getInstance().getRedis()->rpop(topic_->getTopicPath() + ":" + id_);
    return value;
}

void CacheList::lpush(std::string value){
    RedisHandler::getInstance().getRedis()->lpush(topic_->getTopicPath() + ":" + id_, value);
}

std::string CacheList::lpop(){
    std::string value = *RedisHandler::getInstance().getRedis()->lpop(topic_->getTopicPath() + ":" + id_);
    return value;
}

int CacheList::size(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->lrange(topic_->getTopicPath() + ":" + id_, 0, -1, std::back_inserter(value_));
        topic_->removeChangedParameter(id_);
    }
    return static_cast<int>(value_.size());
}

bool CacheList::empty(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->lrange(topic_->getTopicPath() + ":" + id_, 0, -1, std::back_inserter(value_));
        topic_->removeChangedParameter(id_);
    }
    return value_.empty();
}

bool CacheList::contains(std::string value){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->lrange(topic_->getTopicPath() + ":" + id_, 0, -1, std::back_inserter(value_));
        topic_->removeChangedParameter(id_);
    }
    return std::find(value_.begin(), value_.end(), value) != value_.end();
}

void CacheList::clear(){
    value_.clear();
    RedisHandler::getInstance().getRedis()->del(topic_->getTopicPath() + ":" + id_);
}


void CacheMap::addValueToRedis_(){
    for(const auto& pair : value_){
        RedisHandler::getInstance().getRedis()->hset(topic_->getTopicPath() + ":" + id_, pair.first, pair.second);
    }
}

CacheMap::CacheMap(std::string id, std::string topic_path, std::map<std::string, std::string> value) : ContainerCacheValue(id, topic_path){
    value_ = value;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

void CacheMap::setValue(std::map<std::string, std::string> value){
    value_ = value;
    addValueToRedis_();
}

std::any CacheMap::getValue(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->hgetall(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return value_;
}

void CacheMap::addKey(std::string key, std::string val){
    value_[key] = val;
    RedisHandler::getInstance().getRedis()->hset(topic_->getTopicPath() + ":" + id_, key, val);
}

bool CacheMap::contains(std::string key){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->hgetall(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return value_.find(key) != value_.end();
}

void CacheMap::eraseKey(std::string key){
    auto it = value_.find(key);
    if (it != value_.end()) {
        value_.erase(it);
        RedisHandler::getInstance().getRedis()->hdel(topic_->getTopicPath() + ":" + id_, key);
    }
}

std::string CacheMap::getKey(std::string key){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->hgetall(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    auto it = value_.find(key);
    if (it != value_.end()) {
        return it->second;
    }
    else {
        throw std::invalid_argument("Key not found in map.");
    }
}

int CacheMap::size(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->hgetall(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return static_cast<int>(value_.size());
}

bool CacheMap::empty(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->hgetall(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return value_.empty();
}

void CacheMap::clear(){
    value_.clear();
    RedisHandler::getInstance().getRedis()->del(topic_->getTopicPath() + ":" + id_);
}

void CacheSet::addValueToRedis_(){
    for(const auto& val : value_){
        RedisHandler::getInstance().getRedis()->sadd(topic_->getTopicPath() + ":" + id_, val);
    }
}

CacheSet::CacheSet(std::string id, std::string topic_path, std::set<std::string> value) : ContainerCacheValue(id, topic_path){
    value_ = value;
    TopicManager::getInstance().getTopic(topic_path)->addCacheValue(this);
    addValueToRedis_();
}

std::any CacheSet::getValue(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->smembers(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return value_;
}

void CacheSet::setValue(std::set<std::string> value){
    value_ = value;
    addValueToRedis_();
}

void CacheSet::addValue(std::string val){
    value_.insert(val);
    RedisHandler::getInstance().getRedis()->sadd(topic_->getTopicPath() + ":" + id_, val);
}

void CacheSet::removeValue(std::string val){
    value_.erase(val);
    RedisHandler::getInstance().getRedis()->srem(topic_->getTopicPath() + ":" + id_, val);
}

bool CacheSet::contains(std::string val){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->smembers(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return value_.find(val) != value_.end();
}

int CacheSet::size(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->smembers(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return static_cast<int>(value_.size());
}

bool CacheSet::empty(){
    if (topic_->check_changed_parameters().contains(id_)) {
        value_.clear();
        RedisHandler::getInstance().getRedis()->smembers(topic_->getTopicPath() + ":" + id_, std::inserter(value_, value_.begin()));
        topic_->removeChangedParameter(id_);
    }
    return value_.empty();
}

void CacheSet::clear(){
    value_.clear();
    RedisHandler::getInstance().getRedis()->del(topic_->getTopicPath() + ":" + id_);
}