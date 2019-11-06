

#include "RaceCar.h"

#include <utility>
#include "../../../config/constants.h"

#define DEGTORAD (M_PI*1/180)

namespace {

    b2Vec2 processKey(unsigned char key){
        switch (key) {
            case UP : return {1,0};
            case DOWN : return {-1,0};
            case RIGHT : return {0,1};
            case LEFT : return {0,-1};
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
    car_stats.hp -= dmg;
    return isDead();
}

bool RaceCar::isDead() {
    return car_stats.hp<= 0;
}


RaceCar::RaceCar(int carId, InfoBlock stats, b2Body* &newBody) \
            : Entity(newBody) , stats(std::move(stats)), car_stats(stats) {
    this->id = carId;
}

void RaceCar::drive(InfoBlock keys){
    auto key1 =(keys.exists(ACTION_TYPE)) ? keys.get<char>(ACTION_TYPE) : '\n';
    auto key2 =(keys.exists(ACTION_TYPE_DOWN)) ? keys.get<char>(ACTION_TYPE_DOWN) : '\n';
    b2Vec2 v1 = processKey(key1);
    b2Vec2 v2 = processKey(key2);
    this->steer_dir = steer_dir + v1 - v2;
}

void RaceCar::calculateForwardImpulse() {
    float desiredSpeed = 0;
    if (steer_dir.x == 0) {
        car_stats.forward_speed = 0;
        return;
    }
    if (car_stats.forward_speed > car_stats.max_speed){
        car_stats.forward_speed = car_stats.max_speed;
    } else {
        car_stats.forward_speed += car_stats.accel_rate;
    }

    desiredSpeed += steer_dir.x*car_stats.forward_speed;

    //find current speed in forward direction
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot( getForwardVelocity(), currentForwardNormal );

    //apply necessary force
    float force = 2000;
    if ( desiredSpeed < currentSpeed )
        force = -force/4;
    body->ApplyForce( body->GetMass() * force * currentForwardNormal, body->GetWorldCenter(), true);
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
    updateFriction();
    calculateForwardImpulse();

    float desiredTorque = car_stats.rot_force*steer_dir.y;
    body->ApplyTorque( desiredTorque ,true);

}

void RaceCar::loadStateToInfoBlock(InfoBlock& ib) {
    auto pos = body->GetPosition();
    std::string autoId = std::to_string(this->id);
    ib["h" + autoId] = std::round(car_stats.hp);
    ib["x" + autoId] = std::round(pos.x);
    ib["y" + autoId] = std::round(pos.y);
    ib["r" + autoId] = std::round(this->body->GetAngle()/DEGTORAD);
}

b2Vec2 RaceCar::getForwardVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

b2Vec2 RaceCar::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

void RaceCar::updateFriction() {
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    if ( impulse.Length() > 5 )
        impulse *= 30 / impulse.Length();
    body->ApplyLinearImpulse( impulse, body->GetWorldCenter() ,false);
    body->ApplyAngularImpulse( 0.1f * body->GetInertia() * -body->GetAngularVelocity(),true);
    b2Vec2 forwardNormal = getForwardVelocity();
    float currentForwardSpeed = forwardNormal.Normalize();
    float dragForceMagnitude = -2 * currentForwardSpeed;
    body->ApplyForce( dragForceMagnitude * forwardNormal, body->GetWorldCenter() , true);
}