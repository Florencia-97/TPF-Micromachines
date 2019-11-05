

#ifndef MICROMACHINES_RACECAR_H
#define MICROMACHINES_RACECAR_H

#include "CarStats.h"
#include "Entity.h"
#include "../../../common/infostream/InfoBlock.h"
#include "../status_effects/StatusEffect.h"
#include <list>
#include <pthread.h>

class RaceCar : public Entity {
    b2Vec2 accel;
    b2Vec2 steer_dir;
    int rot_goal;
    int health;
    CarStats car_stats;

    b2Vec2 getForwardVelocity();

    b2Vec2 getLateralVelocity();

    void updateFriction();

    void calculateForwardImpulse();

public:
    int id;
    InfoBlock stats;
    std::list<std::shared_ptr<StatusEffect>> status_effects;
    RaceCar(int carId, InfoBlock stats, b2Body* &newBody);
    //POS advances the car simulation one timestep
    void step(float timestep);

    //PRE info block must contain the user key inputs to convert into accel direction
    //under the names key1, key2
    //POS interprets the keys and calculateAccel() in the given direction
    void drive(InfoBlock keys);

    //POS the car takes damage and returns true if life went below 0
    bool takeDamage(int dmg);

    bool isDead();

    //POS parses the car's current status into an infoblock with keys
    // {x, y, r, hp}
    void loadStateToInfoBlock(InfoBlock& ib);
};

#endif //MICROMACHINES_RACECAR_H
