#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <iostream>
#include "../utils/RefCounter.hpp" 


template <typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
public:
    T* ptr;
    RefCounter* counter;

private:
    void release() {
        if (counter && counter->decrement() == 0) {
            std::cout << "[DEALLOC] Object deleted (count=0)\n";
            delete ptr;
            delete counter;
        }
    }

public:

    explicit SharedPtr(T* rawPtr = nullptr)
        : ptr(rawPtr), counter(new RefCounter()) {
        std::cout << "[SharedPtr] Created (count = " << counter->get() << ")\n";
    }


    SharedPtr(const WeakPtr<T>& weak)
        : ptr(weak.ptr), counter(weak.counter) {
        if (counter) counter->increment();
        std::cout << "[SharedPtr] Created from WeakPtr (count = " << counter->get() << ")\n";
    }


    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr), counter(other.counter) {
        if (counter) counter->increment();
        std::cout << "[SharedPtr] Copied (count = " << counter->get() << ")\n";
    }


    SharedPtr(SharedPtr&& other) noexcept
        : ptr(other.ptr), counter(other.counter) {
        other.ptr = nullptr;
        other.counter = nullptr;
        std::cout << "[SharedPtr] Moved\n";
    }


    ~SharedPtr() {
        release();
    }


    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            counter = other.counter;
            if (counter) counter->increment();
            std::cout << "[SharedPtr] Assigned (count = " << counter->get() << ")\n";
        }
        return *this;
    }

    // Move Assignment
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            counter = other.counter;
            other.ptr = nullptr;
            other.counter = nullptr;
            std::cout << "[SharedPtr] Move assigned\n";
        }
        return *this;
    }

  
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }

    int use_count() const {
        return counter ? counter->get() : 0;
    }

    bool unique() const {
        return use_count() == 1;
    }
};

#endif // SHARED_PTR_HPP
