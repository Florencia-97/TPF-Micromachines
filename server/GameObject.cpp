

#include "GameObject.h"

GameObject::GameObject(uint16 type, b2Body* &newBody) {
    this->body = newBody;
    this->type = type;
    this->x_size = 0;
    this->y_size = 0;
    this->enabled = true;

    body->SetUserData(this);
}


void GameObject::attachFixture(b2FixtureDef &boxFixtureDef){
    body->CreateFixture(&boxFixtureDef);
}

void GameObject::resolveCollision(b2Fixture &collidedWith) {
    //do nothing (for now)
}

b2Vec2 GameObject::getPosition() {
    return this->body->GetPosition();
}

b2Vec2 GameObject::getSize() {
    return b2Vec2(x_size,y_size);
}

float32 GameObject::getAngle(){
    return body->GetAngle();
}