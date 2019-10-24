
#include "GameWorld.h"

//local use namespace for local functions
namespace {
    b2Body* makeNewBody(b2World &world, b2BodyType bodyType){
        b2BodyDef myBodyDef;
        myBodyDef.type = bodyType;
        myBodyDef.angle = 0;
        return world.CreateBody(&myBodyDef);
    }

    void createAndAddFixture(GameObject* obj, int hx, int hy, int density,
            uint16 catBits, uint16 maskBits){

        b2PolygonShape boxShape;
        boxShape.SetAsBox(hx, hy);
        b2FixtureDef boxFixtureDef;
        boxFixtureDef.shape = &boxShape;
        boxFixtureDef.density = density;
        boxFixtureDef.filter.categoryBits = catBits;
        boxFixtureDef.filter.maskBits = maskBits;
        obj->attachFixture(boxFixtureDef);
    }
}
void GameWorld::createBackgroundObject() {
    b2Body* newBody = makeNewBody(world, b2_staticBody);
    this->background_objs.emplace_back(newBody);

    createAndAddFixture(&(this->background_objs.back()), 1, 1, 0, GRASS, ROAD_SENSOR);
}

RaceCar& GameWorld::createCar(std::string &carStats) {
    b2Body* newBody = makeNewBody(world, b2_dynamicBody);
    cars.emplace_back(1, carStats, newBody);
}
