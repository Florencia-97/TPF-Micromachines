

#ifndef MICROMACHINES_CARSTATS_H
#define MICROMACHINES_CARSTATS_H

#include "../../../common/infostream/InfoBlock.h"
#include "../../config/constants.h"

class CarStats {
    InfoBlock base;
    int base_hp;
    int base_rot_force;
    int base_max_speed;
    int base_accel_rate;
    
public:
    float max_speed;
    float rot_force;
    float accel_rate;

    int hp;
    int laps;
    float forward_speed;
    //other

    explicit CarStats(InfoBlock ib);
    void step();
};


#endif //MICROMACHINES_CARSTATS_H
