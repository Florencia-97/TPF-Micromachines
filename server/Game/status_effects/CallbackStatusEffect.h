

#ifndef MICROMACHINES_CALLBACKSTATUSEFFECT_H
#define MICROMACHINES_CALLBACKSTATUSEFFECT_H

#include "StatusEffect.h"

class CallbackStatusEffect : public StatusEffect {
    std::function<void()> function;
    
public:
    CallbackStatusEffect(std::string id, std::function<void()> apply_func, double delay);
    
    void applyEffect(CarStats& stats) override;
};


#endif //MICROMACHINES_CALLBACKSTATUSEFFECT_H
