#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

#include <iostream>
#include "RefCounter.hpp"

template <typename T>
class SharedPtr;  // forward declaration

template <typename T>
class WeakPtr {
private:
    T* ptr;
    RefCounter* counter;

public:
    // Constructor from SharedPtr
    WeakPtr(const SharedPtr<T>& shared)
        : ptr(shared.ptr), counter(shared.counter) {
        std::cout << "[WeakPtr] Created (non-owning).\n";
    }

    // Copy constructor
    WeakPtr(const WeakPtr& other)
        : ptr(other.ptr), counter(other.counter) {
        std::cout << "[WeakPtr] Copied.\n";
    }

    // Destructor
    ~WeakPtr() {
        std::cout << "[WeakPtr] Destroyed.\n";
    }

    // Lock: returns a SharedPtr if object is still alive
    SharedPtr<T> lock() const {
        if (counter && counter->get() > 0) {
            return SharedPtr<T>(*this);  // custom constructor needed
        }
        return SharedPtr<T>(nullptr);
    }

    bool expired() const {
        return !counter || counter->get() == 0;
    }
};

#endif // WEAK_PTR_HPP
