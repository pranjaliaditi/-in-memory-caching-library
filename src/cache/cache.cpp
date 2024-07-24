#ifndef CACHE_CPP
#define CACHE_CPP

#include <unordered_map>
#include <memory>
#include <mutex>
#include "../policy/EvictionPolicy.cpp"

template <typename Key, typename Value>
class Cache {
private:
    std::unordered_map<Key, Value> data;
    std::unique_ptr<EvictionPolicy<Key, Value>> evictionPolicy;
    size_t capacity;
    std::mutex mtx;

public:
    Cache(size_t cap, std::unique_ptr<EvictionPolicy<Key, Value>> policy)
        : capacity(cap), evictionPolicy(std::move(policy)) {}

    void put(const Key& key, const Value& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (data.size() >= capacity) {
            Key evictKey = evictionPolicy->evict();
            data.erase(evictKey);
        }
        data[key] = value;
        evictionPolicy->keyAdded(key);
    }

    Value get(const Key& key) {
        std::lock_guard<std::mutex> lock(mtx);
        evictionPolicy->keyAccessed(key);
        return data.at(key);
    }
};

#endif
