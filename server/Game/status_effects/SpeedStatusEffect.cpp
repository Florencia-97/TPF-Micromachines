

#include "SpeedStatusEffect.h"

SpeedStatusEffect::SpeedStatusEffect(int id, double delay, double duration, float speed_mod) {
    this->speed_mod = speed_mod;
    this->id = id;
    this->absorb_stacks = true;
    this->n_stacks = 1;
    this->delay = delay;
    this->duration = duration;
}

void SpeedStatusEffect::applyEffect(CarStats &entity) {
    entity.max_speed = entity.max_speed*speed_mod;
}
