

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

RaceCar::RaceCar(int carId, InfoBlock stats, b2Body* &newBody) \
            : Entity(newBody), car_stats(stats), steer_dir(0,0) {
    this->id = carId;
    body->SetUserData(this);
}

void RaceCar::step(float timestep){
    car_stats.step();
    stepEffects(timestep);

    updateFriction();

    if (isDead())return;
    auto spd = calculateForwardImpulse();
     if (spd > 3 || spd < -3){
        float desiredTorque = car_stats.rot_force * steer_dir.y * this->body->GetMass();
        body->ApplyTorque(desiredTorque, true);
    }
}

bool RaceCar::takeDamage(int dmg) {
    car_stats.hp -= dmg;
    return isDead();
}

bool RaceCar::isDead() {
    return car_stats.hp<= 0;
}


bool RaceCar::addEffect(std::shared_ptr<StatusEffect> &newStatusEffect) {
    for (const auto& status : status_effects) {
        if (status->id == newStatusEffect->id) {
            status->increaseStack(newStatusEffect.get());
            return false;
        }
    }
    status_effects.push_back(newStatusEffect);
    return true;
}

void RaceCar::removeEffect(std::string effectId) {
    for (const auto& status : status_effects) {
        if (status->id == effectId) {
            status->decreaseStack();
            return;
        }
    }
}


void RaceCar::loadStateToInfoBlock(InfoBlock& ib) {
    auto pos = body->GetPosition();
    std::string autoId = std::to_string(this->id);
    ib["h" + autoId] = (int)std::round(car_stats.hp);
    ib["x" + autoId] = (int)std::round(pos.x*PTM);
    ib["y" + autoId] = (int)std::round(pos.y*PTM);
    ib["r" + autoId] = (int)std::round(this->body->GetAngle()/DEGTORAD);
    ib["l" + autoId] = car_stats.laps;
}

void RaceCar::drive(InfoBlock &keys){
    auto key1 =(keys.exists(ACTION_TYPE)) ? keys.get<char>(ACTION_TYPE) : '\n';
    auto key2 =(keys.exists(ACTION_TYPE_DOWN)) ? keys.get<char>(ACTION_TYPE_DOWN) : '\n';
    b2Vec2 v1 = processKey(key1);
    b2Vec2 v2 = processKey(key2);
    this->steer_dir = steer_dir + v1 - v2;
}


b2Vec2 RaceCar::getForwardVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(0,1) );
    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

b2Vec2 RaceCar::getLateralVelocity() {
    b2Vec2 currentRightNormal = body->GetWorldVector( b2Vec2(1,0) );
    return b2Dot( currentRightNormal, body->GetLinearVelocity() ) * currentRightNormal;
}

float RaceCar::calculateForwardImpulse() {
    b2Vec2 currentForwardNormal = body->GetWorldVector( b2Vec2(0,1) );
    float currentSpeed = b2Dot( getForwardVelocity(), currentForwardNormal );

    float desiredSpeed = 0;
    if (steer_dir.x == 0) {
        car_stats.forward_speed = 0;
        if (currentSpeed> -5 && currentSpeed< 5){
            body->SetLinearVelocity(b2Vec2(0,0));
        }
        return currentSpeed;
    }
    if (car_stats.forward_speed > car_stats.max_speed){
        car_stats.forward_speed = car_stats.max_speed;
    } else {
        car_stats.forward_speed += car_stats.accel_rate;
    }

    desiredSpeed += steer_dir.x*car_stats.forward_speed;

    //apply necessary force
    float force = 20 + 320*(std::abs(currentSpeed)/car_stats.max_speed);
    if ( desiredSpeed < currentSpeed )
        force = -force/1.5f;//reverse
    body->ApplyForce( body->GetMass() * force * currentForwardNormal, body->GetWorldCenter(), true);
    //std::cout<<currentSpeed<<" | "<<desiredSpeed<<std::endl;
    return currentSpeed;
}

void RaceCar::updateFriction() {
    b2Vec2 impulse = body->GetMass() * -getLateralVelocity();
    if ( impulse.Length() > 1 )
        impulse *= 10 / impulse.Length();
    body->ApplyLinearImpulse( impulse, body->GetWorldCenter() ,false);

    body->ApplyAngularImpulse( 0.08f * body->GetInertia() * -body->GetAngularVelocity(),true);
    b2Vec2 forwardNormal = getForwardVelocity();
    float currentForwardSpeed = forwardNormal.Normalize();
    float dragForceMagnitude = -1.0f * currentForwardSpeed;
    body->ApplyForce( dragForceMagnitude * forwardNormal, body->GetWorldCenter() , true);
}

void RaceCar::stepEffects(float timestep) {
    bool wasAlive = this->car_stats.hp > 0;
    for (auto i = status_effects.begin(); i!= status_effects.end();){
        auto status = i->get();
        if (status->apply_on_acquire && !status->applied){
            status->applyEffect(car_stats);
        } else if (status->delay > 0){
            status->delay -= timestep;
            i++;
        } else if (status->duration > 0) {
            status->applyEffect(car_stats);
            status->duration -= timestep;
            i++;
        } else if (status->after_effect > 0){
            status->applyEffect(car_stats);
            status->after_effect -= timestep;
            i++;
        } else {
            status->decreaseStack();
            if (status->n_stacks == 0){
                if (status->apply_on_remove) status->applyEffect(car_stats);
                i = status_effects.erase(i);
            }
        }
    }
    if (this->car_stats.hp < 0 && wasAlive){
        //todo boom kill car kaboom
        std::cout<<" CAR DIED KABOOM "<<std::endl;
    }
}

int RaceCar::getLaps() {
    return this->car_stats.laps;
}
