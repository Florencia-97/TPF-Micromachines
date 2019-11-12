

#include "CallbackStatusEffect.h"

#include <utility>

CallbackStatusEffect::CallbackStatusEffect(std::string id, std::function<void()> apply_func, double delay) {
    this->duration = 1;
    this->id = std::move(id);
    this->function = std::move(apply_func);
    this->delay = delay;
    this->after_effect = 0;
    this->apply_on_acquire = false;
    this->apply_on_remove = false;
    this->n_stacks = 1;

}

void CallbackStatusEffect::applyEffect(CarStats &stats) {
    this->function();
    duration = 0;
    applied = true;
}
