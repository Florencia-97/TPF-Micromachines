

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

void Entity::loadPosToInfoBlock(InfoBlock& ib){
    // TODO: for items we need the id, for client to know what to draw!
    auto pos = body->GetPosition();
    std::string itemId = "1"; // hardcoded for now
    ib["Ox" + itemId] = (int)std::round(pos.x);
    ib["Oy" + itemId] = (int)std::round(pos.y);
    //ib["Or" + autoId] = (int)std::round(this->body->GetAngle()/DEGTORAD);
}