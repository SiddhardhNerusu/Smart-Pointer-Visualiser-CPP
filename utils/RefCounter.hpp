#ifndef REF_COUNTER_HPP
#define REF_COUNTER_HPP

#include <iostream>
#include <atomic>

class RefCounter {
private:
    std::atomic<int> count;

public:
    RefCounter() : count(1) {}

    void increment() {
        ++count;
    }

    int decrement() {
        return --count;
    }

    int get() const {
        return count.load();
    }
};

#endif // REF_COUNTER_HPP
