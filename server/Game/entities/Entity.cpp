

#include "Entity.h"

Entity::Entity(b2Body* &newBody) {
    this->body = newBody;
    this->x_size = 0;
    this->y_size = 0;
    this->enabled = true;

    body->SetUserData(this);
}


void Entity::attachFixture(b2FixtureDef &boxFixtureDef){
    body->CreateFixture(&boxFixtureDef);
}

void Entity::resolveCollision(b2Fixture &collidedWith) {
    //do nothing (for now)
}

b2Vec2 Entity::getPosition() {
    return this->body->GetPosition();
}

b2Vec2 Entity::getSize() {
    return b2Vec2(x_size,y_size);
}

float32 Entity::getAngle(){
    return body->GetAngle();
}