#include <iostream>
#include "../include/SharedPtr.hpp"

class Object {
private:
    std::string name;

public:
    explicit Object(const std::string& n) : name(n) {
        std::cout << "[CREATE] Object " << name << " created.\n";
    }

    ~Object() {
        std::cout << "[DESTROY] Object " << name << " destroyed.\n";
    }

    void greet() const {
        std::cout << "Hello from " << name << "!\n";
    }
};

int main() {
    std::cout << "===== Start SharedPtr Test =====\n";

    SharedPtr<Object> ptr1(new Object("Alpha"));
    {
        SharedPtr<Object> ptr2 = ptr1;
        SharedPtr<Object> ptr3 = ptr2;

        std::cout << "Use count inside scope: " << ptr1.use_count() << "\n";
        ptr3->greet();
    }

    std::cout << "Use count after scope: " << ptr1.use_count() << "\n";

    std::cout << "===== End SharedPtr Test =====\n";
    return 0;
}
