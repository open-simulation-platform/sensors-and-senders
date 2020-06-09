#include "UtcTime.h"
#include <cmath>

UtcTime::UtcTime()
    : _start(std::chrono::system_clock::now()) {    
}

double UtcTime::time() const {

    const auto now = std::chrono::system_clock::now();

    std::chrono::duration<double> time_since_start = now - _start;
    
    const auto seconds_since_start = time_since_start.count();

    const auto hours = std::floor(seconds_since_start / 3600.0);
    const auto minutes = std::floor(seconds_since_start / 60.0) - hours * 60;
    const auto seconds = seconds_since_start - hours * 3600 - minutes * 60;

    return hours * 10000 + minutes * 100 + seconds;
}