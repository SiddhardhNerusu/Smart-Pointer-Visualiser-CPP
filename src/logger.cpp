#include <iostream>
#include <string>
#include <chrono>

namespace Logger {
    void log(const std::string& msg) {
        std::cout << "[LOG] " << msg << std::endl;
    }

    void timestamp(const std::string& label) {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();
        std::cout << "[TIME] " << label << " @ " << ms << " ms" << std::endl;
    }
}
