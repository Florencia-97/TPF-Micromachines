
#include "GameWorld.h"

//local use namespace for local functions
namespace {
    b2Body* makeNewBody(b2World &world, b2BodyType bodyType, float32 x, float32 y){
        b2BodyDef myBodyDef;
        myBodyDef.type = bodyType;
        myBodyDef.angle = 0;
        myBodyDef.position.Set(x, y);
        return world.CreateBody(&myBodyDef);
    }

    void createAndAddFixture(Entity* obj, int hx, int hy, int density,
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

GameWorld::GameWorld() : world(b2Vec2(0,0)) {
    //CollisionListener cl;
    //world.SetContactListener(&cl);
}

void GameWorld::Step() {
    for (auto & car : cars){
        car.step();
    }

    float32 timeStep = 1/60.0;//the length of time passed to simulate (seconds)
    int32 velocityIterations = 8;//how strongly to correct velocity
    int32 positionIterations = 3;//how strongly to correct position
    world.Step(timeStep, velocityIterations, positionIterations);
}


void GameWorld::createBackgroundObject() {
    b2Body* newBody = makeNewBody(world, b2_staticBody,0,0);
    this->background_objs.emplace_back(newBody);

    createAndAddFixture(&(this->background_objs.back()), 1, 1, 0, TILE, SENSOR, false);
}

int GameWorld::createCar(InfoBlock carStats) {
    b2Body* newBody = makeNewBody(world, b2_dynamicBody,0,0);
    int carId = cars.size();
    cars.emplace_back(carId, carStats, newBody);

    createAndAddFixture(&(cars.back()),2,1,1,PLAYER, PLAYER, false);
    createAndAddFixture(&(cars.back()),2/2,1/2,0,SENSOR, TILE, true);

    return carId;
}

RaceCar &GameWorld::getCar(int id) {
    return cars.at(id);
}