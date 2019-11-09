

#ifndef MICROMACHINES_LAPCOOLDOWN_H
#define MICROMACHINES_LAPCOOLDOWN_H

#include "StatusEffect.h"

class LapCooldown : public StatusEffect {

public:
    explicit LapCooldown(float duration){
        delay = duration;
        apply_on_remove = false;
        apply_on_acquire = true;
        applied = false;
    };

    void applyEffect(CarStats &entity) override{
        applied = true;
        entity.laps++;
    };

    void increaseStack(StatusEffect* other) override {};

    void decreaseStack() override {};
};


#endif //MICROMACHINES_LAPCOOLDOWN_H
