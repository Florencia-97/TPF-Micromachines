

#include "RaceCar.h"

#include <utility>

namespace {

    b2Vec2 processKey(unsigned char key){
        switch (key) {
            case 'w' : return b2Vec2(1,0);
            case 's' : return b2Vec2(-1,0);
            case 'd' : return b2Vec2(0,-1);
            case 'a' : return b2Vec2(0,1);
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
            : GameObject(newBody) , stats(std::move(stats)) {
    this->health = stats.get<int>("health");
    this->id = carId;
}

void RaceCar::drive(InfoBlock keys){
    auto key1 =(keys.exists("key1")) ? keys.get<char>("key1") : '\n';
    auto key2 =(keys.exists("key2")) ? keys.get<char>("key2") : '\n';
    b2Vec2 v1 = processKey(key1);
    b2Vec2 v2 = processKey((key2 != key1) ? key2 : '\n');
    this->accelerate(v1+v2);
}

b2Vec2 RaceCar::accelerate(b2Vec2 direction){
    float accelRate = (stats.exists("accel_rate") ? stats.getFloat("accel_rate") : 1);
    direction = b2Vec2(direction.x*accelRate, direction.y*accelRate);
    accel = accel + direction;
}

//Q:Why does the step() apply the LinearImpulse and not accelerate?
//A:We still want to apply a linear impulse even when the car did not
//accelerate to simulate the change of speed correctly
void RaceCar::step(){
    b2Vec2 vel = body->GetLinearVelocity();
    float maxVel = (stats.exists("max_speed") ? stats.getFloat("max_speed") : 10);
    float goalVelX = (accel.x > maxVel) ? maxVel : accel.x;
    float goalVelY = (accel.y > maxVel) ? maxVel : accel.y;

    float impulseX = body->GetMass()*(goalVelX - vel.x);
    float impulseY = body->GetMass()*(goalVelY - vel.y);
    body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), body->GetWorldPoint(b2Vec2(1,0)), true);
    float drag_factor = (stats.exists("drag") ? stats.getFloat("drag") : .5);
    accel = b2Vec2(accel.x  * drag_factor, accel.y * drag_factor);
}

InfoBlock RaceCar::stateAsInfoBlock() {
    InfoBlock info("",false);
    info.src_yaml["hp"] = health;
    auto pos = body->GetPosition();
    info.src_yaml["x"] = pos.x ;
    info.src_yaml["y"] = pos.y;
    info.src_yaml["r"] = body->GetAngle();
    
    return info;
}
