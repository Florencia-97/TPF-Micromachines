

#ifndef MICROMACHINES_STATUSEFFECT_H
#define MICROMACHINES_STATUSEFFECT_H

#include "Game/entities/CarStats.h"

class StatusEffect {
protected:
    StatusEffect() = default;
public:
    double duration;
    double delay;
    double after_effect;//duration after duration
    int n_stacks;
    bool absorb_stacks;
    std::string id;

    virtual void applyEffect(CarStats &entity){};

    virtual void increaseStack(StatusEffect* other){n_stacks++;};

    virtual void decreaseStack(){n_stacks--;};
};


#endif //MICROMACHINES_STATUSEFFECT_H
