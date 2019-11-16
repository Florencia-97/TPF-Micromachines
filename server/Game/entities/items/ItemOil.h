
#ifndef MICROMACHINES_ITEMOIL_H
#define MICROMACHINES_ITEMOIL_H

#include <Game/status_effects/DragEffect.h>
#include "../Entity.h"

class ItemOil : public Entity {

    ItemOil(b2Body* &newBody, int itemId);

    void resolveCollision(Entity *collidedWith) override;

    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_ITEMOIL_H
