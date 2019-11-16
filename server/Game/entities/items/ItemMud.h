#ifndef MICROMACHINES_ITEMMUD_H
#define MICROMACHINES_ITEMMUD_H

#include <Game/status_effects/SpeedStatusEffect.h>
#include <Game/entities/Entity.h>

class ItemMud : public Entity{
public:
    SpeedStatusEffect my_effect;
    ItemMud(b2Body* &newBody, int itemId);
    void resolveCollision(Entity *collidedWith) override;
    void endContact(Entity *wasTouching) override;
};


#endif //MICROMACHINES_ITEMMUD_H
