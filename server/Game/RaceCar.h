

#ifndef MICROMACHINES_RACECAR_H
#define MICROMACHINES_RACECAR_H

#include "GameObject.h"

class RaceCar : public GameObject {
    b2Vec2 accel;
    int health;
    int id;
    std::string stats;//TODO yaml with race car stats

public:
    RaceCar(int carId, std::string stats, b2Body* &newBody);

    //PRE x and y must be between [0-1]
    //POS accelerates the car in the specified direction
    b2Vec2 accelerate(b2Vec2 direction);

    //POS advances the car simulation one timestep
    void step();

    //POS the car takes damage and returns true if life went below 0
    bool takeDamage(int dmg);

    bool isDead();
};


#endif //MICROMACHINES_RACECAR_H
