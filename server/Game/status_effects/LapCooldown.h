

#ifndef MICROMACHINES_LAPCOOLDOWN_H
#define MICROMACHINES_LAPCOOLDOWN_H

#include "StatusEffect.h"

class LapCooldown : public StatusEffect {

public:
    explicit LapCooldown(float duration){
        delay = duration;
        apply_on_remove = true;
    };

    void applyEffect(CarStats &entity) override{entity.laps++;};

    void increaseStack(StatusEffect* other) override {};

    void decreaseStack() override {};
};


#endif //MICROMACHINES_LAPCOOLDOWN_H
