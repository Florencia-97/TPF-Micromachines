

#ifndef MICROMACHINES_OFFROAD_H
#define MICROMACHINES_OFFROAD_H

#include "Entity.h"
#include "../status_effects/SpeedStatusEffect.h"

class OffRoad : public Entity {
public:
    SpeedStatusEffect my_effect;
    std::string id;

    explicit OffRoad(std::string id, b2Body* &newBody);

    void resolveCollision(Entity *collidedWith) override;

    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_OFFROAD_H
