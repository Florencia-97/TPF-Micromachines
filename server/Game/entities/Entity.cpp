

#include "Entity.h"

Entity::Entity(b2Body* &newBody) {
    this->body = newBody;
    this->x_size = 0;
    this->y_size = 0;
    this->enabled = true;
    this->id = 0; // Change
    body->SetUserData(this);
}

Entity::Entity(b2Body* &newBody, int id){
    // TODO: refactor, quick copy paste for testing
    this->body = newBody;
    this->x_size = 0;
    this->y_size = 0;
    this->enabled = true;
    this->id = id;
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
    // TODO: for items we need the id, for client to know what to draw!
    auto pos = body->GetPosition();
    std::string itemId = std::to_string(this->id); // hardcoded for now
    std::string num = std::to_string(cont);
    ib["Ox" + itemId] = (int)std::round(pos.x);
    ib["Oy" + itemId] = (int)std::round(pos.y);
    ib["Ot" + itemId] = 1; // hardcoded, here goes the tile number!;
    ib["OId"+ num] = this->id;
}

b2Body *Entity::getBody() {
    return this->body;
}
