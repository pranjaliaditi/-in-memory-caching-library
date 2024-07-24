#include <iostream>
#include "cache/cache.cpp"
#include "policy/FIFOEvictionPolicy.cpp"
#include "policy/LRUEvictionPolicy.cpp"
#include "policy/LIFOEvictionPolicy.cpp"

// Main function for running
int main() {

    // Test FIFO Cache
    auto fifoPolicy = std::make_unique<FIFOEvictionPolicy<int, std::string>>();
    Cache<int, std::string> fifoCache(3, std::move(fifoPolicy));

    fifoCache.put(1, "one");
    fifoCache.put(2, "two");
    fifoCache.put(3, "three");
    std::cout << "FIFO Cache: " << fifoCache.get(1) << std::endl; // Outputs "one"
    fifoCache.put(4, "four"); // Evicts "one"
    try {
        std::cout << fifoCache.get(1) << std::endl; // Should throw an error
    } catch (const std::exception& e) {
        std::cout << "FIFO Cache: Key 1 evicted" << std::endl;
    }

    // Test LRU Cache
    auto lruPolicy = std::make_unique<LRUEvictionPolicy<int, std::string>>();
    Cache<int, std::string> lruCache(3, std::move(lruPolicy));

    lruCache.put(1, "one");
    lruCache.put(2, "two");
    lruCache.put(3, "three");
    lruCache.get(2);
    lruCache.put(4, "four"); // Evicts "two"
    try {
        std::cout << lruCache.get(1) << std::endl; // Should throw an error
    } catch (const std::exception& e) {
        std::cout << "LRU Cache: Key 1 evicted" << std::endl;
    }

    // Test LIFO Cache
    auto lifoPolicy = std::make_unique<LIFOEvectionPolicy<int, std::string>>();
    Cache<int, std::string> lifoCache(3, std::move(lifoPolicy));

    lifoCache.put(1, "one");
    lifoCache.put(2, "two");
    lifoCache.put(3, "three");
    std::cout << "LIFO Cache: " << lifoCache.get(3) << std::endl; // Outputs "three"
    lifoCache.put(4, "four"); // Evicts "three"
    try {
        std::cout << lifoCache.get(3) << std::endl; // Should throw an error
    } catch (const std::exception& e) {
        std::cout << "LIFO Cache: Key 3 evicted" << std::endl;
    }

    return 0;
}
