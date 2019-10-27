

#ifndef MICROMACHINES_STOPWATCH_H
#define MICROMACHINES_STOPWATCH_H

#include <chrono>

#define SEC_TO_MIL 1000
#define FRAME_RATE 1/60


class Stopwatch {
    std::chrono::duration<double, std::milli>  t1;
public:

    //POS creates a Stopwatch and calls setNow()
    Stopwatch();

    //POS sets t1 to 0
    void setNow();

    //POS adds a delta d in milliseconds to t1
    void addDelta(double d);

    //POS returns the difference between now and t1 in milliseconds
    double diff();



};


#endif //MICROMACHINES_STOPWATCH_H
