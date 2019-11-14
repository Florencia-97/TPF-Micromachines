

#include "HealthEffect.h"

void HealthEffect::applyEffect(CarStats &entity) {
    if (apply_on_acquire){
        applied = true;
        duration = 0;
        delay = 0;
        entity.hp = std::max(0, entity.hp + power);
    } else if (current_tick == 0){
        entity.hp = std::max(0, entity.hp + power);
    }
    current_tick = (++current_tick)%interval;
    if (state_mod_enabled){
        entity.state += state_mod;
    }
}

HealthEffect::HealthEffect(std::string id, bool apply_on_get, double delay, double duration, int power, int interval_frames)
        : StatusEffect() {

    this->power = power;
    this->id = std::move(id);
    this->n_stacks = 1;
    this->delay = delay;
    this->duration = duration;
    this->after_effect = 0;
    this->apply_on_acquire = apply_on_get;
    this->apply_on_remove = false;
    this->interval = std::max(1,interval_frames);
    this->current_tick = 1;

}

void HealthEffect::increaseStack(StatusEffect *other) {

    if (n_stacks == 0){
        this->duration = other->duration;
        this->delay = other->delay;
    }
    this->n_stacks++;
}

void HealthEffect::decreaseStack() {
    if (n_stacks == 0) return;
    this->n_stacks--;
    if (n_stacks == 0){
        this->delay =0;
        this->duration = 0;
    }
}
