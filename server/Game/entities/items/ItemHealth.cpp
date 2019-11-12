#include "ItemHealth.h"
#include "../../../../config/constants.h"
#define ITEM_HEALTH_UP "ITEM_HEALTH_UP"

ItemHealth::ItemHealth(b2Body *&newBody, int itemId) :
        Entity(newBody, itemId, ITEM_HEALTH), my_effect(ITEM_HEALTH_UP, true, 0.5, 10, 10, 2){
}

void ItemHealth::resolveCollision(Entity *other) {
    // TODO: Add right numbers!
    std::cout << "Colision with health\n" << std::endl;
    auto ptr = std::shared_ptr<StatusEffect>(new HealthEffect(ITEM_HEALTH_UP, my_effect.apply_on_acquire, my_effect.delay,
                                                                   my_effect.duration, 10, 2));
    other->addEffect(ptr);
}

void ItemHealth::endContact(Entity *wasTouching) {
    wasTouching->removeEffect(ITEM_HEALTH_UP);
}