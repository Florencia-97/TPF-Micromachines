

#ifndef MICROMACHINES_RACECAR_H
#define MICROMACHINES_RACECAR_H

#include "CarStats.h"
#include "Entity.h"
#include "../../../common/infostream/InfoBlock.h"
#include "../status_effects/StatusEffect.h"
#include <list>
#include <pthread.h>

class RaceCar : public Entity {
    b2Vec2 steer_dir;
    std::list<std::shared_ptr<StatusEffect>> status_effects;

    b2Vec2 getForwardVelocity();

    b2Vec2 getLateralVelocity();

    void updateFriction();

    float calculateForwardImpulse();

public:
    CarStats car_stats;
    int id;
    
    RaceCar(int carId, InfoBlock stats, b2Body* &newBody);
    //POS advances the car simulation one timestep
    void step(float timestep);

    //PRE info block must contain the user key inputs to convert into accel direction
    //under the names key1, key2
    //POS interprets the keys and calculateAccel() in the given direction
    void drive(InfoBlock &keys);

    //POS the car takes damage and returns true if life went below 0
    bool takeDamage(int dmg);

    bool isDead();

    int getLaps();

    //POS parses the car's current status into an infoblock with keys
    // {x, y, r, hp}
    void loadStateToInfoBlock(InfoBlock& ib);

    bool addEffect(std::shared_ptr<StatusEffect> &newStatusEffect) override;

    void removeEffect(std::string effectId) override;

    void stepEffects(float timestep);
};

#endif //MICROMACHINES_RACECAR_H
