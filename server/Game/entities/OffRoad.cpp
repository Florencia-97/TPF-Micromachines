

#include "OffRoad.h"
#define OFFROAD_SLOW "OFF_ROAD_SLOW"
#define OFFROAD_DMG "OFF_ROAD_DAMAGE"

OffRoad::OffRoad(std::string id, b2Body *&newBody) : Entity(newBody),
                                                     my_effect(OFFROAD_SLOW, 0.5, 10000, 0, .5){
    body->SetUserData(this);
    this->id = id;
}

void OffRoad::resolveCollision(Entity *other) {
    //std::cout<<"touched: "<<id<<std::endl;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(OFFROAD_SLOW, my_effect.delay,
                                             my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);
    auto damage_ptr = std::shared_ptr<StatusEffect>(new HealthEffect(OFFROAD_DMG, false,
                                             my_effect.delay, my_effect.duration, -5, 80));
    other->addEffect(damage_ptr);

}


void OffRoad::endContact(Entity *wasTouching) {
    wasTouching->removeEffect(OFFROAD_SLOW);
    wasTouching->removeEffect(OFFROAD_DMG);
}
