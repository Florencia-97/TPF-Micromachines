#include "ItemBoost.h"
#define ITEM_SPEED_BOOST "ROAD_SPEED_BOOST"

ItemBoost::ItemBoost(b2Body *&newBody) :
    Entity(newBody), my_effect(ITEM_SPEED_BOOST,0,10000,.5,2){
    body->SetUserData(this); // Do i need this?
}

void ItemBoost::resolveCollision(Entity *other) {
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ITEM_SPEED_BOOST,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
}

void ItemBoost::endContact(Entity *wasTouching) {
    wasTouching->removeEffect(ITEM_SPEED_BOOST);
}