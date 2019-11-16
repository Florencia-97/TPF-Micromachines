
#include "DragEffect.h"

DragEffect::DragEffect(std::string id, double delay, double duration, float rot_mod) {
    this->id = std::move(id);
    this->n_stacks = 1;
    this->delay = delay;
    this->duration = duration;
    this->rot_mod = rot_mod;
    this->after_effect = 0;
}

void DragEffect::applyEffect(CarStats &entity) {
    entity.rot_force = entity.rot_force*rot_mod;
    if (state_mod_enabled){
        entity.state += state_mod;
    }
}

void DragEffect::increaseStack(StatusEffect *other) {
    if (n_stacks == 0){
        this->duration = other->duration;
        this->delay = other->delay;
        this->after_effect = other->after_effect;
    }
    this->n_stacks++;
}

void DragEffect::decreaseStack() {
    if (n_stacks == 0) return;
    this->n_stacks--;
    if (n_stacks == 0){
        this->delay =0;
        this->duration = 0;
    }
}
