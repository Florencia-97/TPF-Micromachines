#include "CarStats.h"

CarStats::CarStats(InfoBlock ib){
    this->laps = -1;
    this->base = ib;
    this->base_max_speed = ib.get<int>(MAX_SPEED);
    this->base_rot_force = ib.get<int>(ROTATION_FORCE);
    this->forward_speed = 0;
    this->base_hp = ib.get<int>(HEALTH);
    this->hp = base_hp;
    this->base_accel_rate = ib.get<int>(ACCELERATION);
    max_speed = this->base_max_speed;
    this->rot_force = this->base_rot_force;
    this->hp = this->base_hp;
    this->accel_rate = this->base_accel_rate;
}

void CarStats::step() {
    max_speed = this->base_max_speed;
    this->rot_force = this->base_rot_force;
    this->accel_rate = this->base_accel_rate;
}
