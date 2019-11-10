#ifndef MICROMACHINES_ITEMBOOST_H
#define MICROMACHINES_ITEMBOOST_H

#include <Game/status_effects/SpeedStatusEffect.h>
#include "../Entity.h"

// Increase in car speed
class ItemBoost : Entity{
public:
    SpeedStatusEffect my_effect;
    explicit ItemBoost(b2Body* &newBody);
    void resolveCollision(Entity *collidedWith) override;
    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_ITEMBOOST_H
