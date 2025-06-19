#include "../include/UniquePtr.hpp"

class MyObject {
public:
    MyObject() { std::cout << "[MyObject] Constructor\n"; }
    ~MyObject() { std::cout << "[MyObject] Destructor\n"; }

    void greet() const {
        std::cout << "Hello from MyObject!\n";
    }
};

int main() {
    {
        UniquePtr<MyObject> ptr1(new MyObject());
        ptr1->greet();

        UniquePtr<MyObject> ptr2 = std::move(ptr1);  // move it
        if (!ptr1.isValid()) std::cout << "ptr1 is now empty.\n";

        ptr2.reset(new MyObject());  // reset
        MyObject* raw = ptr2.release();  // release ownership

        delete raw;  // manual cleanup
    }

    return 0;
}
