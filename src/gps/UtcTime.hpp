#pragma once 
#include <chrono>

class UtcTime {
public:
    UtcTime();

    double time() const;

private:

    std::chrono::time_point<std::chrono::system_clock> _start;
};