// Timer.hpp
#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class TimerClock {
private:
    std::chrono::high_resolution_clock::time_point start_time;
public:
    TimerClock();
    void reset();
    double elapsed();
};

#endif // TIMER_HPP
