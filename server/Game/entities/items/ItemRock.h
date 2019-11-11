#ifndef MICROMACHINES_ITEMROCK_H
#define MICROMACHINES_ITEMROCK_H

#include <Game/status_effects/SpeedStatusEffect.h>
#include "../Entity.h"

// Reduces life and speed
class ItemRock : public Entity {
public:
    SpeedStatusEffect my_effect;
    ItemRock(b2Body* &newBody, int itemId);
    void resolveCollision(Entity *collidedWith) override;
    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_ITEMROCK_H
