

#ifndef MICROMACHINES_SPEEDSTATUSEFFECT_H
#define MICROMACHINES_SPEEDSTATUSEFFECT_H

#include "StatusEffect.h"

class SpeedStatusEffect : public StatusEffect {
public:
    float speed_mod;

    SpeedStatusEffect(int id, double delay, double duration, float speed_mod);

    void applyEffect(CarStats& entity) override;
};


#endif //MICROMACHINES_SPEEDSTATUSEFFECT_H
