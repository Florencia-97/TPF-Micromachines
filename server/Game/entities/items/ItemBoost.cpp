#include "ItemBoost.h"
#include "../../../../config/constants.h"
#define ITEM_SPEED_BOOST "ITEM_SPEED_BOOST"

ItemBoost::ItemBoost(b2Body *&newBody, int itemId) :
    Entity(newBody, itemId, ITEM_BOOST), my_effect(ITEM_SPEED_BOOST,0,4,0,1.5){
}

void ItemBoost::resolveCollision(Entity *other) {
    if (!enabled) return;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ITEM_SPEED_BOOST,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
    this->enabled = false;
}

void ItemBoost::endContact(Entity *wasTouching) {
    //wasTouching->removeEffect(ITEM_SPEED_BOOST);
}