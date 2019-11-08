

#ifndef MICROMACHINES_CARSTATS_H
#define MICROMACHINES_CARSTATS_H

#include "../../../common/infostream/InfoBlock.h"

class CarStats {
public:
    InfoBlock base;
    float max_speed;
    float rot_force;
    float accel_rate;

    int hp;
    int laps{0};
    float forward_speed;
    //other

    explicit CarStats(InfoBlock ib);
    void step();
};


#endif //MICROMACHINES_CARSTATS_H
