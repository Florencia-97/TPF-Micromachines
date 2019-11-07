

#include "PhysicalRoad.h"
#define ROAD_SPEED_BOOST "ROAD_SPEED_BOOST"

void PhysicalRoad::resolveCollision(Entity *other) {
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ROAD_SPEED_BOOST,my_effect.delay,
            my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
}

PhysicalRoad::PhysicalRoad(b2Body *&newBody) : Entity(newBody),
            my_effect(ROAD_SPEED_BOOST,0,10000,.5,1.4){
    body->SetUserData(this);
}

void PhysicalRoad::endContact(Entity *wasTouching) {
    wasTouching->removeEffect(ROAD_SPEED_BOOST);
}
