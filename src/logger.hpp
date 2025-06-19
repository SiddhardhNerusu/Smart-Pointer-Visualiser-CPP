#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

namespace Logger {
    void log(const std::string& msg);
    void timestamp(const std::string& label);
}

#endif
