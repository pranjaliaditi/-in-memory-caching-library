#ifndef LIFO_POLICY_CPP
#define LIFO_POLICY_CPP

#include "EvictionPolicy.cpp"
#include <list>

template <typename Key, typename Value>
class LIFOEvectionPolicy : public EvictionPolicy<Key, Value> {
private:
    std::list<Key> order;

public:
    void keyAccessed(const Key& key) override {
        // LIFO does nothing on access
    }

    void keyAdded(const Key& key) override {
        order.push_back(key);
    }

    Key evict() override {
        Key evictKey = order.back();
        order.pop_back();
        return evictKey;
    }
};

#endif
