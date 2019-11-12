#ifndef MICROMACHINES_ITEMHEALTH_H
#define MICROMACHINES_ITEMHEALTH_H

#include "Game/status_effects/HealthEffect.h"
#include "../Entity.h"

class ItemHealth : public Entity {
public:
    HealthEffect my_effect;
    ItemHealth(b2Body* &newBody, int itemId);
    void resolveCollision(Entity *collidedWith) override;
    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_ITEMHEALTH_H
