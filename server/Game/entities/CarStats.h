

#ifndef MICROMACHINES_CARSTATS_H
#define MICROMACHINES_CARSTATS_H

#include "../../../common/InfoBlock.h"

class CarStats {
public:
    InfoBlock base;
    float hp;
    float max_speed;
    //other

    CarStats() = default;

    void step();
};


#endif //MICROMACHINES_CARSTATS_H
