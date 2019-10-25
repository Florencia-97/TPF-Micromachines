

#include "RaceCar.h"

bool RaceCar::takeDamage(int dmg) {
    this->health -= dmg;
    return isDead();
}

bool RaceCar::isDead() {
    return health <= 0;
}

//TODO get stats from yaml
RaceCar::RaceCar(int carId, std::string stats, b2Body* &newBody) \
            : GameObject(newBody) {
    this->health = 10;
    this->id = carId;
    this->stats = stats;
}

b2Vec2 RaceCar::accelerate(b2Vec2 direction){
    direction = b2Vec2(direction.x, direction.y);// * stats.accel_speed TODO
    accel = accel + direction;
}

//Q:Why does the step() apply the LinearImpulse and not accelerate?
//A:We still want to apply a linear impulse even when the car did not
//accelerate to simulate the change of speed correctly
void RaceCar::step(){
    b2Vec2 vel = body->GetLinearVelocity();
    float maxVel = 10;//yaml stats.max_speed TODO
    float goalVelX = (accel.x > maxVel) ? maxVel : accel.x;
    float goalVelY = (accel.y > maxVel) ? maxVel : accel.y;

    float impulseX = body->GetMass()*(goalVelX - vel.x);
    float impulseY = body->GetMass()*(goalVelY - vel.y);
    body->ApplyLinearImpulse(b2Vec2(impulseX, impulseY), body->GetWorldPoint(b2Vec2(1,0)), true);
    float dampening_factor = .8;//from stats TODO
    accel = b2Vec2(accel.x  * dampening_factor, accel.y * dampening_factor);
}