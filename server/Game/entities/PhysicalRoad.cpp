

#include "PhysicalRoad.h"
#define ROAD_SPEED_BOOST "ROAD_SPEED_BOOST"

PhysicalRoad::PhysicalRoad(std::string id, b2Body *&newBody) : Entity(newBody),
            my_effect(ROAD_SPEED_BOOST,0,10000,.5,4){
    body->SetUserData(this);
    this->id = id;
}

void PhysicalRoad::resolveCollision(Entity *other) {
    //std::cout<<"touched: "<<id<<std::endl;
    auto ptr = std::shared_ptr<StatusEffect>(new SpeedStatusEffect(ROAD_SPEED_BOOST,my_effect.delay,
                                                                   my_effect.duration, my_effect.after_effect, my_effect.speed_mod));
    other->addEffect(ptr);

}


void PhysicalRoad::endContact(Entity *wasTouching) {
    //std::cout<<"ended: "<<id<<std::endl;
    wasTouching->removeEffect(ROAD_SPEED_BOOST);
}
