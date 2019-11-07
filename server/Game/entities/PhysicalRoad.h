

#ifndef MICROMACHINES_PHYSICALROAD_H
#define MICROMACHINES_PHYSICALROAD_H

#include "Entity.h"
#include "../status_effects/SpeedStatusEffect.h"

class PhysicalRoad : public Entity {
public:
    SpeedStatusEffect my_effect;

    explicit PhysicalRoad(b2Body* &newBody);

    void resolveCollision(Entity *collidedWith) override;

    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_PHYSICALROAD_H
