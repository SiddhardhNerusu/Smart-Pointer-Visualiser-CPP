#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <iostream>

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {
        std::cout << "[UniquePtr] Created with object at " << ptr << "\n";
    }

    // Destructor
    ~UniquePtr() {
        std::cout << "[UniquePtr] Destroying object at " << ptr << "\n";
        delete ptr;
    }

    // Delete Copy Constructor and Copy Assignment (no copy allowed)
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move Constructor
    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
        std::cout << "[UniquePtr] Moved\n";
    }

    // Move Assignment
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
            std::cout << "[UniquePtr] Move assigned\n";
        }
        return *this;
    }

    // Dereference
    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    // Check if not null
    bool isValid() const {
        return ptr != nullptr;
    }

    // Manually release ownership
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        std::cout << "[UniquePtr] Released ownership\n";
        return temp;
    }

    // Reset with new pointer
    void reset(T* newPtr = nullptr) {
        delete ptr;
        ptr = newPtr;
        std::cout << "[UniquePtr] Reset to new object at " << ptr << "\n";
    }
};

#endif // UNIQUE_PTR_HPP
