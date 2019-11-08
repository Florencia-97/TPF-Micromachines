

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

b2Vec2 Entity::getPosition() {
    return this->body->GetPosition();
}

b2Vec2 Entity::getSize() {
    return b2Vec2(x_size,y_size);
}

float32 Entity::getAngle(){
    return body->GetAngle();
}

void Entity::loadPosToInfoBlock(InfoBlock& ib, int cont){
    auto pos = body->GetPosition();
    std::string itemId = std::to_string(cont);
    ib["Ox" + itemId] = (int)std::round(pos.x);
    ib["Oy" + itemId] = (int)std::round(pos.y);
    //ib["Or" + autoId] = (int)std::round(this->body->GetAngle()/DEGTORAD);
}