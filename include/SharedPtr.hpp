#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <iostream>
#include <atomic>

template<typename T>
class SharedPtr {
private:
    T* ptr;
    std::atomic<int>* refCount;

    void release() {
        if (refCount && --(*refCount) == 0) {
            std::cout << "[DEALLOC] Deleting object and ref counter\n";
            delete ptr;
            delete refCount;
        }
    }

public:
    // Constructor
    explicit SharedPtr(T* rawPtr = nullptr)
        : ptr(rawPtr), refCount(new std::atomic<int>(1)) {
        std::cout << "[CREATE] SharedPtr created. Ref count = " << *refCount << "\n";
    }

    // Copy Constructor
    SharedPtr(const SharedPtr& other)
        : ptr(other.ptr), refCount(other.refCount) {
        ++(*refCount);
        std::cout << "[COPY] SharedPtr copied. Ref count = " << *refCount << "\n";
    }

    // Move Constructor
    SharedPtr(SharedPtr&& other) noexcept
        : ptr(other.ptr), refCount(other.refCount) {
        other.ptr = nullptr;
        other.refCount = nullptr;
        std::cout << "[MOVE] SharedPtr moved.\n";
    }

    // Destructor
    ~SharedPtr() {
        release();
    }

    // Assignment Operator
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            ++(*refCount);
            std::cout << "[ASSIGN] SharedPtr assigned. Ref count = " << *refCount << "\n";
        }
        return *this;
    }

    // Move Assignment
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            refCount = other.refCount;
            other.ptr = nullptr;
            other.refCount = nullptr;
            std::cout << "[MOVE ASSIGN] SharedPtr move-assigned.\n";
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    int use_count() const {
        return refCount ? *refCount : 0;
    }

    bool unique() const {
        return use_count() == 1;
    }
};

#endif // SHARED_PTR_HPP
