#ifndef FIFO_POLICY_CPP
#define FIFO_POLICY_CPP

#include "EvictionPolicy.cpp"
#include <list>

template <typename Key, typename Value>
class FIFOEvictionPolicy : public EvictionPolicy<Key, Value> {
private:
    std::list<Key> order;

public:
    void keyAccessed(const Key& key) override {
        // FIFO does nothing on access
    }

    void keyAdded(const Key& key) override {
        order.push_back(key);
    }

    Key evict() override {
        Key evictKey = order.front();
        order.pop_front();
        return evictKey;
    }
};

#endif
