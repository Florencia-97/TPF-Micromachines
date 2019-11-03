

#include "RaceCar.h"

#include <utility>
#include "../../../config/constants.h"

namespace {

    b2Vec2 processKey(unsigned char key){
        switch (key) {
            case UP : return b2Vec2(1,0);
            case DOWN : return b2Vec2(-1,0);
            case RIGHT : return b2Vec2(0,-1);
            case LEFT : return b2Vec2(0,1);
            default: return b2Vec2(0,0);
        }
    }

}

bool RaceCar::takeDamage(int dmg) {
    this->health -= dmg;
    return isDead();
}

bool RaceCar::isDead() {
    return health <= 0;
}


RaceCar::RaceCar(int carId, InfoBlock stats, b2Body* &newBody) \
            : Entity(newBody) , stats(std::move(stats)), car_stats(stats) {
    this->health = stats.get<int>(HEALTH);
    this->id = carId;
}

void RaceCar::drive(InfoBlock keys){
    auto key1 =(keys.exists("key")) ? keys.get<char>("key") : '\n';
    b2Vec2 v1 = processKey(key1);
    this->accelerate(v1);
}

b2Vec2 RaceCar::accelerate(b2Vec2 direction){
    float accelRate = (stats.exists("accel_rate") ? stats.getFloat("accel_rate") : 100);
    direction = b2Vec2(direction.x*accelRate, direction.y*accelRate);
    accel = accel + direction;
}

//Q:Why does the step() apply the LinearImpulse and not accelerate?
//A:We still want to apply a linear impulse even when the car did not
//accelerate to simulate the change of speed correctly
void RaceCar::step(float timestep){
    car_stats.step();
    for (auto status : status_effects){
        if (status->delay > 0){
            status->delay -= timestep;
        } else if (status->duration > 0) {
            status->applyEffect(car_stats);
            status->duration -= timestep;
        }
    }


    b2Vec2 vel = body->GetLinearVelocity();
    float maxVel = (stats.exists("max_speed") ? stats.getFloat("max_speed") : 10);
    float goalVelX = (accel.x > maxVel) ? maxVel : accel.x;
    float goalVelY = (accel.y > maxVel) ? maxVel : accel.y;

    float impulseX = body->GetMass()* 1/2;//(goalVelX - vel.x);
    float impulseY = body->GetMass()* 1/2;//(goalVelY - vel.y);
    body->ApplyForce(b2Vec2(impulseX, impulseY), body->GetWorldPoint(b2Vec2(1,0)), true);
    float drag_factor = (stats.exists("drag") ? stats.getFloat("drag") : 0);
    accel = b2Vec2(accel.x  * drag_factor, accel.y * drag_factor);
}

void RaceCar::loadStateToInfoBlock(InfoBlock& ib) {
    auto pos = body->GetPosition();
    std::string autoId = std::to_string(this->id);
    ib["h" + autoId] = std::round(health);
    ib["x" + autoId] = std::round(pos.x);
    ib["y" + autoId] = std::round(pos.y);
    ib["r" + autoId] = std::round(this->body->GetAngle());
    std::cout<<"x: "<<pos.x<< " y: "<<pos.y<<std::endl;
}
