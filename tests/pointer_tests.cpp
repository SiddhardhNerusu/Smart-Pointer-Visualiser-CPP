#include "../include/SharedPtr.hpp"
#include "../include/WeakPtr.hpp"
#include "../include/logger.hpp"

class TestObject {
public:
    int id;
    TestObject(int id) : id(id) {}
    void say() {
        std::cout << "Object ID: " << id << std::endl;
    }
};

int main() {
    Logger::log("Test 1: Basic SharedPtr creation");
    SharedPtr<TestObject> sp1(new TestObject(100));
    sp1->say();

    Logger::log("Test 2: SharedPtr Copy and Ref Count");
    SharedPtr<TestObject> sp2 = sp1;
    std::cout << "Ref count after copy: " << sp1.use_count() << std::endl;

    Logger::log("Test 3: WeakPtr from SharedPtr");
    WeakPtr<TestObject> wp = sp1;
    std::cout << "Is expired? " << wp.expired() << std::endl;

    Logger::log("Test 4: Locking WeakPtr into SharedPtr");
    if (auto locked = wp.lock()) {
        locked->say();
        std::cout << "Locked use count: " << locked.use_count() << std::endl;
    }

    Logger::log("Test 5: Resetting SharedPtr");
    sp1 = nullptr;
    std::cout << "After reset, sp2 count: " << sp2.use_count() << std::endl;

    Logger::log("Test 6: Letting all SharedPtrs go out of scope");
    {
        SharedPtr<TestObject> temp = sp2;
        std::cout << "Inside scope count: " << temp.use_count() << std::endl;
    }

    Logger::log("Test 7: Expiry after all SharedPtrs are gone");
    sp2 = nullptr;
    std::cout << "Is expired now? " << wp.expired() << std::endl;

    Logger::timestamp("End of tests");
    return 0;
}
