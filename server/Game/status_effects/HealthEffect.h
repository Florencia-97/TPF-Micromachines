

#ifndef MICROMACHINES_HEALTHEFFECT_H
#define MICROMACHINES_HEALTHEFFECT_H

#include "StatusEffect.h"

class HealthEffect : public StatusEffect {
    int interval;
    int current_tick;
    int power;

public:

    HealthEffect(std::string id, bool apply_on_get, double delay, double duration, int power, int interval);

    void applyEffect(CarStats& entity) override;

    void increaseStack(StatusEffect *other) override;

    void decreaseStack() override;
};


#endif //MICROMACHINES_HEALTHEFFECT_H
