

#include "GameObject.h"

GameObject::GameObject(int type, b2Body* &newBody, int xSize, int ySize) {
    this->body = newBody;
    this->type = type;
    this->x_size = xSize;
    this->y_size = ySize;

    b2PolygonShape boxShape;
    boxShape.SetAsBox(xSize, ySize);
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;

    body->CreateFixture(&boxFixtureDef);
    body->SetUserData(this);
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
