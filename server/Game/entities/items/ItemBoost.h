#ifndef MICROMACHINES_ITEMBOOST_H
#define MICROMACHINES_ITEMBOOST_H

#include <Game/status_effects/SpeedStatusEffect.h>
#include "../Entity.h"

// Boost in car speed
class ItemBoost : public Entity{
public:
    SpeedStatusEffect my_effect;
    ItemBoost(b2Body* &newBody, int itemId);
    void resolveCollision(Entity *collidedWith) override;
    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_ITEMBOOST_H
