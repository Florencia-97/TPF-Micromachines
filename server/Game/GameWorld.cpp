
#include <iostream>
#include "GameWorld.h"
#include "../../config/constants.h"

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

void GameWorld::loadWorld(std::string worldName){
    // TODO load box2D world with the mapNumber given
    worldName = "race_1"; //Change for real names afterwards!!
    YAML::Node config = YAML::LoadFile("maps/" + worldName + ".yaml");
    YAML::Node mapYaml = config["Map"];
    int y = 0;
    int x = 0;
    int rowTile = -1;
    int num = 1;

    for (YAML::iterator it = mapYaml.begin(); it != mapYaml.end(); ++it) {
        rowTile += 1;
        x = 0;

        int columnTile = 0;
        const YAML::Node &row = *it;
        std::string numberRow = std::to_string(num);
        YAML::Node column = row[numberRow];
        int colNum = 0;

        for (YAML::iterator c = column.begin(); c != column.end(); ++c) {
            y = rowTile * 512;
            x = columnTile * 512;
            const YAML::Node &col_value = *c;

            int numberTile = col_value.as<int>();
            this->createBackgroundObject(x, y, numberTile);

            colNum++;
            columnTile += 1;
        }

        num++;
    }
}

InfoBlock GameWorld::status(){
    // TODO: create a real infoblock with the new world
    InfoBlock ib;
    ib[PLAYERS_AMOUNT] = this->cars.size();
    for (auto & car : cars){
        std::string car_id = std::to_string(car.id);
        car.stateAsString(ib);
    }
    std::cout << ib.srcString() << std::endl;
    ib[OBJECTS_AMOUNT] = 0; // here goes something like this->objects.size();
/*    int cont = 0;
    for (auto & obj : objects){
        std::string obj_id = std::to_string(cont);
        ib["O" + obj_id] = obj.stateAsInfoBlock();
        cont++;
    }*/
    return ib;
}

void GameWorld::processEvent(InfoBlock event){
    // TODO : process event in physic world
    std::cout << event.srcString() << std::endl;
    return;
}

void GameWorld::Step() {
    float32 timeStep = 1/60.0;//the length of time passed to simulate (seconds)
    for (auto & car : cars){
        car.step(timeStep);
    }

    int32 velocityIterations = 8;//how strongly to correct velocity
    int32 positionIterations = 3;//how strongly to correct position
    world.Step(timeStep, velocityIterations, positionIterations);
}


void GameWorld::createBackgroundObject(int x, int y, int tileType) {
    // TODO: load proper tile depending in tileType given
    b2Body* newBody = makeNewBody(world, b2_staticBody, x, y);
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