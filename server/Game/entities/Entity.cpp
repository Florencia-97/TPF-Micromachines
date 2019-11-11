

#include "Entity.h"

Entity::Entity(b2Body* &newBody) {
    this->body = newBody;
    this->x_size = 0;
    this->y_size = 0;
    this->enabled = true;
    this->id = 0;
    this->tileId = 1;
    body->SetUserData(this);
}

Entity::Entity(b2Body* &newBody, int id, const int tile){
    // TODO: refactor, quick copy paste for testing
    this->body = newBody;
    this->x_size = 0;
    this->y_size = 0;
    this->enabled = true;
    this->id = id;
    this->tileId = tile;
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

void Entity::loadPosToInfoBlock(InfoBlock& ib, int cont) {
    auto pos = body->GetPosition();
    std::string itemId = std::to_string(this->id);
    std::string num = std::to_string(cont);
    ib["OId" + num] = this->id;
    ib["Ox" + itemId] = (int) std::round(pos.x);
    ib["Oy" + itemId] = (int) std::round(pos.y);
    ib["Ot" + itemId] = this->tileId;
}

b2Body *Entity::getBody() {
    return this->body;
}
