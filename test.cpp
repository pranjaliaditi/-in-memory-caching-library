#include <iostream>
#include <cassert>
#include "src/cache/cache.cpp"
#include "src/policy/FIFOEvictionPolicy.cpp"
#include "src/policy/LRUEvictionPolicy.cpp"
#include "src/policy/LIFOEvictionPolicy.cpp"

void runTests() {
    // Test FIFO Cache
    {
        auto fifoPolicy = std::make_unique<FIFOEvictionPolicy<int, std::string>>();
        Cache<int, std::string> fifoCache(3, std::move(fifoPolicy));

        fifoCache.put(1, "one");
        fifoCache.put(2, "two");
        fifoCache.put(3, "three");
        assert(fifoCache.get(1) == "one");
        fifoCache.put(4, "four"); // Evicts "one"
        try {
            fifoCache.get(1);
            std::cout << "Test failed: Key 1 should have been evicted" << std::endl;
        } catch (const std::exception&) {
            std::cout << "FIFO Cache Test Passed" << std::endl;
        }
    }

    // Test LRU Cache
    {
        auto lruPolicy = std::make_unique<LRUEvictionPolicy<int, std::string>>();
        Cache<int, std::string> lruCache(3, std::move(lruPolicy));

        lruCache.put(1, "one");
        lruCache.put(2, "two");
        lruCache.put(3, "three");
        lruCache.get(1);
        lruCache.put(4, "four"); // Evicts "two"
        try {
            lruCache.get(2);
            std::cout << "Test failed: Key 2 should have been evicted" << std::endl;
        } catch (const std::exception&) {
            std::cout << "LRU Cache Test Passed" << std::endl;
        }
    }

    // Test LIFO Cache
    {
        auto lifoPolicy = std::make_unique<LIFOEvectionPolicy<int, std::string>>();
        Cache<int, std::string> lifoCache(3, std::move(lifoPolicy));

        lifoCache.put(1, "one");
        lifoCache.put(2, "two");
        lifoCache.put(3, "three");
        assert(lifoCache.get(3) == "three");
        lifoCache.put(4, "four"); // Evicts "three"
        try {
            lifoCache.get(3);
            std::cout << "Test failed: Key 3 should have been evicted" << std::endl;
        } catch (const std::exception&) {
            std::cout << "LIFO Cache Test Passed" << std::endl;
        }
    }
}

int main() {
    runTests();
    return 0;
}
