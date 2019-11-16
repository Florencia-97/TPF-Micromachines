#include "ItemMud.h"
#include "../../../../config/constants.h"
#define ITEM_SPEED_DROP "MUD_SPD_DWN"

ItemMud::ItemMud(b2Body *&newBody, int itemId) :
        Entity(newBody, itemId, ITEM_MUD), my_effect(ITEM_SPEED_DROP,0,4,0,0.5){
}

void ItemMud::resolveCollision(Entity *other) {
    if (!enabled) return;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ITEM_SPEED_DROP,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
    ptr->setStateModifActive("MUD");
    enabled = false;
}

void ItemMud::endContact(Entity *wasTouching) {
    //wasTouching->removeEffect(ITEM_SPEED_DROP);
}