

#include "Stopwatch.h"

Stopwatch::Stopwatch() {
    this->reset();
}

void Stopwatch::reset() {
    t1 = clock();
}

double Stopwatch::diff() {
    clock_t t2 = clock();
    return double(t2-t1);
}


void Stopwatch::addDelta(double d){
    this->t1 += d;
}
