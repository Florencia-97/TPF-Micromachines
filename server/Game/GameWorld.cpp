
#include <iostream>
#include "GameWorld.h"
#include "../../config/constants.h"
#include "status_effects/SpeedStatusEffect.h"

//local use namespace for local functions
namespace {
    b2Body* makeNewBody(b2World &world, b2BodyType bodyType, float32 x, float32 y){
        b2BodyDef myBodyDef;
        myBodyDef.type = bodyType;
        myBodyDef.angle = 0;
        myBodyDef.position.Set(x, y);
        return world.CreateBody(&myBodyDef);
    }

    void createAndAddFixture(Entity* obj, float hx, float hy, float density,
                             uint16 catBits, uint16 maskBits, bool isSensor){

        b2PolygonShape boxShape;
        boxShape.SetAsBox(hx/2, hy/2);
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
    world.SetContactListener(&cl);
}

void GameWorld::loadWorld(std::string worldName){
    map.load("maps/" + worldName+".yaml");
    for (int j = 0; j<map.road.size(); j++){
        auto row = map.road[j];
        for (int i= 0; i<row.size();i++){
            if (row[i] <= ROAD_END_TYPE && row[i] >= ROAD_START_TYPE){
                createRoad(i * TILE_SIZE + TILE_SIZE/2 , j*TILE_SIZE + TILE_SIZE/2, row[i]);
            }
        }
    }
}

InfoBlock GameWorld::status(){
    InfoBlock ib;
    ib[PLAYERS_AMOUNT] = this->cars.size();
    for (auto & car : cars){
        std::string car_id = std::to_string(car.id);
        car.loadStateToInfoBlock(ib);
    }
    //todo finish sending objects
    ib[OBJECTS_AMOUNT] = 0; // here goes something like this->objects.size();
/*    int cont = 0;
    for (auto & obj : objects){
        std::string obj_id = std::to_string(cont);
        ib["O" + obj_id] = obj.stateAsInfoBlock();
        cont++;
    }*/
    return ib;
}

void GameWorld::processEvent(int id, InfoBlock event){
    getCar(id).drive(event);
}

void GameWorld::Step(float timestep) {
    for (auto & car : cars){
        car.step(timestep);
        //car.dummyMove();
    }

    int32 velocityIterations = 8;//how strongly to correct velocity
    int32 positionIterations = 3;//how strongly to correct position
    world.Step(timestep, velocityIterations, positionIterations);
}


void GameWorld::createRoad(int x, int y, int tileType) {
    b2Body* newBody = makeNewBody(world, b2_staticBody, x, y);
    this->road_bodies.emplace_back(std::to_string(tileType)+"x: "+ std::to_string(x/512) + " y: "+std::to_string(y/512),newBody);
    createAndAddFixture(&(this->road_bodies.back()), TILE_SIZE, TILE_SIZE, 0, TILE, SENSOR, false);
}

int GameWorld::createCar(InfoBlock carStats) {
    b2Body* newBody = makeNewBody(world, b2_dynamicBody,1000 + cars.size()*150,1000+cars.size()*150);
    int carId = cars.size();
    cars.emplace_back(carId, carStats, newBody);

    createAndAddFixture(&(cars.back()),1,2,.1,PLAYER, 0, false);
    createAndAddFixture(&(cars.back()),CAR_WIDTH,CAR_HEIGHT,0,PLAYER, PLAYER, false);
    createAndAddFixture(&(cars.back()),1,1,0,SENSOR, TILE, true);
    return carId;
}

RaceCar &GameWorld::getCar(int id) {
    auto it = cars.begin();
    for (int i = 0; i<id;i++){
        it++;
    }
    return *it;
}