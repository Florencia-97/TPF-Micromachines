

#include "Stopwatch.h"

constexpr auto steady_min = std::chrono::steady_clock::time_point::min();

Stopwatch::Stopwatch() {
    setNow();
}

void Stopwatch::setNow() {
    auto last_frame = steady_min;
    std::chrono::duration<double, std::milli> zero_t {0.0F};
    t1 = zero_t;
}

double Stopwatch::diff() {
    auto t2 = std::chrono::steady_clock::now();
    auto d = t2-t1;
    std::chrono::duration<double, std::milli> t {d};
    return t.count();
}


void Stopwatch::addDelta(double d){
    std::chrono::duration<double, std::milli> t {d};
    this->t1 += t;
}
