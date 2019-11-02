

#ifndef MICROMACHINES_CARSTATS_H
#define MICROMACHINES_CARSTATS_H

#include "../../../common/infostream/InfoBlock.h"

class CarStats {
public:
    InfoBlock base;
    float hp;
    float max_speed;
    //other

    explicit CarStats(InfoBlock ib);
    void step();
};


#endif //MICROMACHINES_CARSTATS_H
