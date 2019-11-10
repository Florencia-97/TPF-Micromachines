#include "ItemRock.h"
#define ITEM_ROCK_SPEED_DOWN "ROAD_SPEED_BOOST"

ItemRock::ItemRock(b2Body *&newBody) :
        Entity(newBody), my_effect(ITEM_ROCK_SPEED_DOWN,0,10000,.5,2){
    body->SetUserData(this); // Do i need this?
}

void ItemRock::resolveCollision(Entity *other) {
    // can i reduce entity health here?
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ITEM_ROCK_SPEED_DOWN,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
}

void ItemRock::endContact(Entity *wasTouching) {
    wasTouching->removeEffect(ITEM_ROCK_SPEED_DOWN);
}