

#include "RaceCar.h"

bool RaceCar::takeDamage(int dmg) {
    this->health -= dmg;
    return isDead();
}

bool RaceCar::isDead() {
    return health <= 0;
}

//TODO get stats from yaml
RaceCar::RaceCar(int carId, std::string stats, b2Body* &newBody) \
            : GameObject(newBody) {
    this->health = 10;
    this->id = carId;
    this->stats = stats;
}
