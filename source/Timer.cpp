// Timer.cpp
#include "..\headers\Timer.hpp"

TimerClock::TimerClock() : start_time(std::chrono::high_resolution_clock::now()) {}

void TimerClock::reset() {
    start_time = std::chrono::high_resolution_clock::now();
}

double TimerClock::elapsed() {
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed_seconds = end_time - start_time;
    return elapsed_seconds.count();
}
