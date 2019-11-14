#include <Game/status_effects/HealthEffect.h>
#include "ItemRock.h"
#include "../../../../config/constants.h"
#define ITEM_ROCK_SPEED_DOWN "ITEM_ROCK_SPEED_DOWN"

ItemRock::ItemRock(b2Body *&newBody, int itemId) :
        Entity(newBody, itemId, ITEM_ROCK), my_effect(ITEM_ROCK_SPEED_DOWN,0,0,2,.75){
}

void ItemRock::resolveCollision(Entity *other) {
    if (!enabled) return;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ITEM_ROCK_SPEED_DOWN,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
    auto h_ptr = std::shared_ptr<StatusEffect>(new HealthEffect("ROCK_DMG", true,0,0, -15,0));
    other->addEffect(h_ptr);
    enabled = false;
}

void ItemRock::endContact(Entity *wasTouching) {
    //wasTouching->removeEffect(ITEM_ROCK_SPEED_DOWN);
}