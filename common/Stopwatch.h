

#ifndef MICROMACHINES_STOPWATCH_H
#define MICROMACHINES_STOPWATCH_H


#include <ctime>

#define SEC_TO_MIL 1000
#define FRAME_RATE 1/60


class Stopwatch {
    clock_t t1;
public:

    //creates a stopwatch set at t1 = now
    Stopwatch();

    //POS sets t1 to now
    void reset();

    //POS returns the difference between now and t1 in seconds
    double diff();



};


#endif //MICROMACHINES_STOPWATCH_H
