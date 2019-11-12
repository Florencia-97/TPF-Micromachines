#include "ItemRock.h"
#include "../../../../config/constants.h"
#define ITEM_ROCK_SPEED_DOWN "ROAD_SPEED_BOOST"

ItemRock::ItemRock(b2Body *&newBody, int itemId) :
        Entity(newBody, itemId, ITEM_ROCK), my_effect(ITEM_ROCK_SPEED_DOWN,0,0,2,.75){
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