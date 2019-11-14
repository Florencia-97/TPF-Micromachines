#include "ItemOil.h"
#include "../../../../config/constants.h"
#define ITEM_SPEED_DROP "MUD_SPD_DWN"

ItemOil::ItemOil(b2Body *&newBody, int itemId) :
        Entity(newBody, itemId, ITEM_OIL), my_effect(ITEM_SPEED_DROP,0,4,0,0.5){
}

void ItemOil::resolveCollision(Entity *other) {
    if (!enabled) return;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ITEM_SPEED_DROP,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
    ptr->setStateModifActive("MUD");
    enabled = false;
}

void ItemOil::endContact(Entity *wasTouching) {
    //wasTouching->removeEffect(ITEM_SPEED_DROP);
}