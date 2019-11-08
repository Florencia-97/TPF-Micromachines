

#include "SpeedStatusEffect.h"

#include <utility>

SpeedStatusEffect::SpeedStatusEffect(std::string id, double delay, double duration, double after_effect, float speed_mod) {
    this->speed_mod = speed_mod;
    this->id = std::move(id);
    this->n_stacks = 1;
    this->delay = delay;
    this->duration = duration;
    this->after_effect = after_effect;
}

void SpeedStatusEffect::applyEffect(CarStats &entity) {
    entity.max_speed = entity.max_speed*speed_mod;
}

void SpeedStatusEffect::increaseStack(StatusEffect *other) {

    if (n_stacks == 0){
        this->duration = other->duration;
        this->delay = other->delay;
        this->after_effect = other->after_effect;
    }
    this->n_stacks++;
}

void SpeedStatusEffect::decreaseStack() {
    if (n_stacks == 0) return;
    this->n_stacks--;
    if (n_stacks == 0){
        this->delay =0;
        this->duration = 0;
    }
}

