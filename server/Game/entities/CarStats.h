

#ifndef MICROMACHINES_CARSTATS_H
#define MICROMACHINES_CARSTATS_H

#include "../../../common/infostream/InfoBlock.h"

class CarStats {
    InfoBlock base;
public:
    int base_hp;
    int base_rot_force;
    int base_max_speed;
    int base_accel_rate;
    float max_speed;
    float rot_force;
    float accel_rate;
    std::string state;

    int hp;
    int laps;
    float forward_speed;
    //other

    explicit CarStats(InfoBlock ib);
    void step();
};


#endif //MICROMACHINES_CARSTATS_H
