

#ifndef MICROMACHINES_STATUSEFFECT_H
#define MICROMACHINES_STATUSEFFECT_H

#include <utility>

#include "Game/entities/CarStats.h"

class StatusEffect {
protected:
    StatusEffect(){
        duration = 0;
        delay = 0;
        after_effect = 0;
        n_stacks = 0;
        apply_on_remove = false;
        apply_on_acquire = false;
        applied = false;
        state_mod = "";
        state_mod_enabled = false;
    };
    
public:
    double duration{0};
    double delay{0};
    double after_effect{0};//duration after duration
    int n_stacks{0};
    bool apply_on_remove{false};
    bool apply_on_acquire{false};
    bool applied{false};
    std::string id;
    std::string state_mod;
    bool state_mod_enabled;

    virtual void applyEffect(CarStats &entity){};

    virtual void increaseStack(StatusEffect* other){n_stacks++;};

    virtual void decreaseStack(){n_stacks--;};

    void setStateModifActive(std::string mod){
        state_mod = std::move(mod);
        this->state_mod_enabled = true;
    };
};


#endif //MICROMACHINES_STATUSEFFECT_H
