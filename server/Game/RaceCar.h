

#ifndef MICROMACHINES_RACECAR_H
#define MICROMACHINES_RACECAR_H

#include "Entity.h"
#include "../../common/InfoBlock.h"
#include <set>

class RaceCar : public Entity {
    b2Vec2 accel;
    int health;

public:
    int id;
    InfoBlock stats;

    RaceCar(int carId, InfoBlock stats, b2Body* &newBody);

    //POS advances the car simulation one timestep
    void step();

    //PRE x and y must be between [0-1]
    //POS accelerates the car in the specified direction
    b2Vec2 accelerate(b2Vec2 direction);

    //PRE info block must contain the user key inputs to convert into accel direction
    //under the names key1, key2
    //POS interprets the keys and accelerate() in the given direction
    void drive(InfoBlock keys);

    //POS the car takes damage and returns true if life went below 0
    bool takeDamage(int dmg);

    bool isDead();

    //POS parses the car's current status into an infoblock with keys
    // {x, y, r, hp}
    InfoBlock stateAsInfoBlock();
};

#endif //MICROMACHINES_RACECAR_H
