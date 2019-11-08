

#ifndef MICROMACHINES_FINISHINGLINE_H
#define MICROMACHINES_FINISHINGLINE_H

#include "Entity.h"
#include "Game/status_effects/LapCooldown.h"

class FinishingLine : public Entity {
public:
    explicit FinishingLine(b2Body* &newBody) : Entity(newBody){};

    //void resolveCollision(Entity *collidedWith) override;

    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_FINISHINGLINE_H
