
#include "GameWorld.h"

void GameWorld::createBackgroundObject() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.angle = 0;
    b2Body* newBody = world.CreateBody(&myBodyDef);

    this->background_objs.emplace_back(GRASS,newBody);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(1, 1);
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1;
    boxFixtureDef.filter.categoryBits = GRASS;
    boxFixtureDef.filter.maskBits = ROAD_SENSOR;

    this->background_objs.back().attachFixture(boxFixtureDef);
}
