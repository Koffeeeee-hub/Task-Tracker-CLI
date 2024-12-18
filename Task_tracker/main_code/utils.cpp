#ifndef UTILS_CPP
#define UTILS_CPP

#include <iostream>
#include <chrono>
#include <string>

// Returns the current time and date in string format
std::string get_current_time() {
    std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
    std::time_t tt;
    tt = std::chrono::system_clock::to_time_t(time);
    std::string thetime = ctime(&tt);
    thetime.erase(thetime.find('\n', 0), 1);
    return thetime;
}

#endif
