

#ifndef MICROMACHINES_REDLINECOOLDOWN_H
#define MICROMACHINES_REDLINECOOLDOWN_H

#include "StatusEffect.h"

class RedlineCooldown : public StatusEffect {

public:
    void increaseStack(StatusEffect* other) override {};

    void decreaseStack() override {};
};


#endif //MICROMACHINES_REDLINECOOLDOWN_H
