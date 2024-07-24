#ifndef LRU_POLICY_CPP
#define LRU_POLICY_CPP

#include "EvictionPolicy.cpp"
#include <list>
#include <unordered_map>

template <typename Key, typename Value>
class LRUEvictionPolicy : public EvictionPolicy<Key, Value> {
private:
    std::list<Key> order;
    std::unordered_map<Key, typename std::list<Key>::iterator> keyIterMap;

public:
    void keyAccessed(const Key& key) override {
        if (keyIterMap.find(key) != keyIterMap.end()) {
            order.erase(keyIterMap[key]);
            order.push_front(key);
            keyIterMap[key] = order.begin();
        }
    }

    void keyAdded(const Key& key) override {
        order.push_front(key);
        keyIterMap[key] = order.begin();
    }

    Key evict() override {
        Key evictKey = order.back();
        order.pop_back();
        keyIterMap.erase(evictKey);
        return evictKey;
    }
};

#endif
