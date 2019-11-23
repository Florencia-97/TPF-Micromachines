

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
        id = "laps";
    };

    explicit LapCooldown(float duration, bool dont_add_lap){
        delay = duration;
        apply_on_remove = false;
        apply_on_acquire = true;
        applied = dont_add_lap;
        id = "laps";
    };

    void applyEffect(CarStats &entity) override{
        if (applied) return;
        applied = true;
        entity.laps++;
    };

    void increaseStack(StatusEffect* other) override {
        delay = other->delay;//refresh
    };

    void decreaseStack() override {};
};


#endif //MICROMACHINES_LAPCOOLDOWN_H
