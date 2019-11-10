#ifndef MICROMACHINES_ITEMROCK_H
#define MICROMACHINES_ITEMROCK_H

#include <Game/status_effects/SpeedStatusEffect.h>
#include "../Entity.h"

// Reduces life and speed
class ItemRock : Entity {
public:
    SpeedStatusEffect my_effect;
    explicit ItemRock(b2Body* &newBody);
    void resolveCollision(Entity *collidedWith) override;
    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_ITEMROCK_H
