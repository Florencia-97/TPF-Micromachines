
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
            uint16 catBits, uint16 maskBits, bool isSensor){

        b2PolygonShape boxShape;
        boxShape.SetAsBox(hx, hy);
        b2FixtureDef boxFixtureDef;
        boxFixtureDef.shape = &boxShape;
        boxFixtureDef.density = density;
        boxFixtureDef.filter.categoryBits = catBits;
        boxFixtureDef.filter.maskBits = maskBits;
        boxFixtureDef.isSensor = isSensor;
        obj->attachFixture(boxFixtureDef);
    }
}
void GameWorld::createBackgroundObject() {
    b2Body* newBody = makeNewBody(world, b2_staticBody);
    this->background_objs.emplace_back(newBody);

    createAndAddFixture(&(this->background_objs.back()), 1, 1, 0, GRASS, ROAD_SENSOR, false);
}

int GameWorld::createCar(std::string &carStats) {
    b2Body* newBody = makeNewBody(world, b2_dynamicBody);
    int carId = cars.size();
    cars.emplace_back(carId, carStats, newBody);

    createAndAddFixture(&(cars.back()),2,1,1,PLAYER, PLAYER, false);
    createAndAddFixture(&(cars.back()),2,1,1,ROAD_SENSOR, GRASS | ROAD, true);

    return carId;
}

RaceCar &GameWorld::getCar(int id) {
    return cars.at(id);
}

void GameWorld::Step() {

}
