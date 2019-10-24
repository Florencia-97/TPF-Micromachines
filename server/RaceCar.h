

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

    //POS applies acceleration in a given direction
    //void Accelerate(b2Vec2 accDir);

    //pos applies the dampening to the acceleration and other "over time" mods to stats
    //void Step();

    //POS the car takes damage and returns true if life went below 0
    bool takeDamage(int dmg);

    bool isDead();
};


#endif //MICROMACHINES_RACECAR_H
