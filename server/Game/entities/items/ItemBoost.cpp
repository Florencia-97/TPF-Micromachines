#include "ItemBoost.h"
#include "../../../../config/constants.h"
#define ITEM_SPEED_BOOST "ITEM_SPEED_BOOST"

ItemBoost::ItemBoost(b2Body *&newBody, int itemId) :
    Entity(newBody, itemId, ITEM_BOOST), my_effect(ITEM_SPEED_BOOST,0,3000,.5,2.0){
    body->SetUserData(this);
}

void ItemBoost::resolveCollision(Entity *other) {
    std::cout << "colision with boost\n" << std::endl;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ITEM_SPEED_BOOST,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
}

void ItemBoost::endContact(Entity *wasTouching) {
    wasTouching->removeEffect(ITEM_SPEED_BOOST);
}