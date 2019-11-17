
#ifndef MICROMACHINES_DRAGEFFECT_H
#define MICROMACHINES_DRAGEFFECT_H

#include "StatusEffect.h"

class DragEffect : public StatusEffect{
    float rot_mod;

public:
    DragEffect(std::string id, double delay, double duration, float rot_mod);

    void applyEffect(CarStats& entity) override;

    void increaseStack(StatusEffect* other) override;

    void decreaseStack() override;
};


#endif //MICROMACHINES_DRAGEFFECT_H
