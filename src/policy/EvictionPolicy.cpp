#ifndef EVICTION_POLICY_CPP
#define EVICTION_POLICY_CPP

template <typename Key, typename Value>
class EvictionPolicy {
public:
    virtual ~EvictionPolicy() = default;
    virtual void keyAccessed(const Key& key) = 0;
    virtual void keyAdded(const Key& key) = 0;
    virtual Key evict() = 0;
};

#endif
