#include "CarStats.h"

CarStats::CarStats(InfoBlock ib){
    this->base = ib;
    max_speed = 500;
    this->rot_force = 5;
    this->forward_speed = 0;
    this->hp = 100;
    this->accel_rate = 10;
}

void CarStats::step() {
    max_speed = 500;
    this->rot_force = 6;
    this->hp = 100;
    this->accel_rate = 10;
}
