

#include "OffRoad.h"
#define ROAD_SPEED_BOOST "ROAD_SPEED_BOOST"

OffRoad::OffRoad(std::string id, b2Body *&newBody) : Entity(newBody),
                                                     my_effect(ROAD_SPEED_BOOST,0,10000,.5,.5){
    body->SetUserData(this);
    this->id = id;
}

void OffRoad::resolveCollision(Entity *other) {
    //std::cout<<"touched: "<<id<<std::endl;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ROAD_SPEED_BOOST,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);

}


void OffRoad::endContact(Entity *wasTouching) {
    //std::cout<<"ended: "<<id<<std::endl;
    wasTouching->removeEffect(ROAD_SPEED_BOOST);
}
