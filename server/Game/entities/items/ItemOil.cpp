
#include "ItemOil.h"
#include "../../../../config/constants.h"

void ItemOil::resolveCollision(Entity *collidedWith) {
    if (!enabled) return;
    auto ptr = std::shared_ptr<StatusEffect>(new DragEffect("Oil",0, 2,.65));

    collidedWith->addEffect(ptr);
    //ptr->setStateModifActive("Oil");
    enabled = false;
}

void ItemOil::endContact(Entity *wasTouching) {
}

ItemOil::ItemOil(b2Body *&newBody, int itemId): Entity(newBody, itemId, ITEM_MUD) {}
