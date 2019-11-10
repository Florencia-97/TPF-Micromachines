

#ifndef MICROMACHINES_STATUSEFFECT_H
#define MICROMACHINES_STATUSEFFECT_H

#include "Game/entities/CarStats.h"

class StatusEffect {
protected:
    StatusEffect() = default;
public:
    double duration{0};
    double delay{0};
    double after_effect{0};//duration after duration
    int n_stacks{0};
    bool apply_on_remove{false};
    bool apply_on_acquire{false};
    bool applied{false};
    std::string id;

    virtual void applyEffect(CarStats &entity){};

    virtual void increaseStack(StatusEffect* other){n_stacks++;};

    virtual void decreaseStack(){n_stacks--;};
};


#endif //MICROMACHINES_STATUSEFFECT_H
