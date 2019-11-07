

#ifndef MICROMACHINES_SPEEDSTATUSEFFECT_H
#define MICROMACHINES_SPEEDSTATUSEFFECT_H

#include "StatusEffect.h"

class SpeedStatusEffect : public StatusEffect {
public:
    float speed_mod;

    SpeedStatusEffect(std::string id, double delay, double duration, double after_effect, float speed_mod);

    void applyEffect(CarStats& entity) override;

    void increaseStack(StatusEffect* other) override;

    void decreaseStack() override;
};


#endif //MICROMACHINES_SPEEDSTATUSEFFECT_H
