

#include "RaceCar.h"

#include <utility>
#include "../../../config/constants.h"

namespace {

    b2Vec2 processKey(unsigned char key){
        switch (key) {
            case UP : return {0,1};
            case DOWN : return {0,-1};
            case RIGHT : return {1,0};
            case LEFT : return {-1,0};
            default: return {0,0};
        }
    }

    float clamp_signed(float a, float absolute_limit){
        if (a > 0){
            return (a > absolute_limit) ? absolute_limit : a;
        } else {
            return (a < -absolute_limit) ? -absolute_limit : a;
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
    accel = b2Vec2(0,0);
}

void RaceCar::drive(InfoBlock keys){
    auto key1 =(keys.exists(ACTION_TYPE)) ? keys.get<char>(ACTION_TYPE) : '\n';
    auto key2 =(keys.exists(ACTION_TYPE_DOWN)) ? keys.get<char>(ACTION_TYPE_DOWN) : '\n';
    b2Vec2 v1 = processKey(key1);
    b2Vec2 v2 = processKey(key2);
    this->steer_dir = steer_dir + v1 - v2;
}

b2Vec2 RaceCar::calculateAccel(b2Vec2 currentSpeed) {
    float accelRate = (stats.exists("accel_rate") ? stats.getFloat("accel_rate") : 20);
    float maxVel = (stats.exists("max_speed") ? stats.getFloat("max_speed") : 200);
    float ax = accel.x + accelRate*steer_dir.x;
    float ay = accel.y + accelRate*steer_dir.y;
    float vx = currentSpeed.x + ax;
    float vy = currentSpeed.y + ay;

    vy = clamp_signed(vx, maxVel);
    vx = clamp_signed(vy, maxVel);
    ax = clamp_signed(ax, maxVel);
    ay = clamp_signed(ay, maxVel);
    accel = b2Vec2(ax, ay);
    return {vx, vy};

}

void RaceCar::step(float timestep){
    car_stats.step();
    for (auto &status : status_effects){
        if (status->delay > 0){
            status->delay -= timestep;
        } else if (status->duration > 0) {
            status->applyEffect(car_stats);
            status->duration -= timestep;
        }
    }

    if (isDead())return;
    b2Vec2 forwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    b2Vec2 lateralNormal = body->GetWorldVector( b2Vec2(1,0) );
    float currentSpeed = b2Dot( getForwardVelocity(), forwardNormal );

    //apply necessary force
    float forceF = 100 * steer_dir.y;
    float forceL = 1 * steer_dir.x;
    float desiredTorque = 10;
    body->ApplyLinearImpulse( forceF * forwardNormal + forceL * lateralNormal,\
            body->GetWorldPoint(b2Vec2(0,-0.5)), true);
}

void RaceCar::loadStateToInfoBlock(InfoBlock& ib) {
    auto pos = body->GetPosition();
    std::string autoId = std::to_string(this->id);
    ib["h" + autoId] = std::round(health);
    ib["x" + autoId] = std::round(pos.x);
    ib["y" + autoId] = std::round(pos.y);
    ib["r" + autoId] = std::round(- this->body->GetAngle());
}

b2Vec2 RaceCar::getForwardVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}