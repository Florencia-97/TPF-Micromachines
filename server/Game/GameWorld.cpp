#include <iostream>
#include <memory>
#include <random>
#include <Game/entities/items/ItemCreator.h>
#include <Game/status_effects/CallbackStatusEffect.h>
#include "GameWorld.h"
#include "../../config/constants.h"


#define PTM_TILE (float)TILE_SIZE/PTM

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
    finishingLine = nullptr;
    timeModifiers = 0;
    itemsId = 0;
}

void GameWorld::loadWorld(std::string worldName){
    map.load("maps/" + worldName+".yaml");

    for (int j = 0; j < map.road.size(); j++){
        auto row = map.road[j];
        for (int i= 0; i<row.size();i++){
            int x = i * PTM_TILE + PTM_TILE / 2;
            int y =  j * PTM_TILE + PTM_TILE / 2;
            if (row[i] == 0){ //not road
                createOffRoad(x, y, row[i]);
            } else {
                Coordinate c;
                c.x = x;
                c.y = y;
                road_positions.push_back(c);
            }
        }
    }
    // TODO: Load  all the extras (the ones you just crash with)
    for (size_t j = 0; j < map.extras.size(); j++){
        auto row = map.extras[j];
        for (size_t i= 0; i < row.size(); i++){
            if (row[i] == finish_line){
                createFinishingLine(i * PTM_TILE + PTM_TILE/2 , j*PTM_TILE + PTM_TILE/2);
            }
            else if (row[i] == pavilion_blue_tile) {
                //createExtras(i * PTM_TILE + PTM_TILE/2 , j*PTM_TILE + PTM_TILE/2, row[i]);
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
    int cont = 0;
    ib[OBJECTS_AMOUNT] = this->dynamic_objs.size();
    for (auto & item : dynamic_objs){
        item->loadPosToInfoBlock(ib, cont);
        cont++;
    }
    return ib;
}

void GameWorld::processEvent(int id, InfoBlock &event){
    getCar(id).drive(event);
}

void GameWorld::Step(float timeStep) {
    for (auto & car : cars) {
        bool wasAlive = car.car_stats.hp > 0;
        _explodeIfOutOfBounds(car);
        car.step(timeStep);
        if (car.car_stats.hp <= 0 && wasAlive) {
            respawnCar(car);
        }
    }

    int32 velocityIterations = 8;//how strongly to correct velocity
    int32 positionIterations = 3;//how strongly to correct position
    world.Step(timeStep, velocityIterations, positionIterations);
    this->timeModifiers += timeStep;

    stepItems();
    attempItemSpawn();

}

RaceCar &GameWorld::getCar(int id) {
    auto it = cars.begin();
    for (int i = 0; i<id;i++){
        it++;
    }
    return *it;
}

void GameWorld::_createItem(){
    int x = 0;
    int y = 0;
    int x0 = 0, y0=0;
    _loadXYInRoad(x, y);
    x0 = (x < map.width/2) ? -10 : map.width + 10;
    y0 = (x < map.height/2) ? -10 : map.height + 10;
    b2Body* newBody = makeNewBody(world, b2_dynamicBody, x0, y0);
    auto ptr = ItemCreator::createItem(newBody, itemsId);
    ptr->setTargetPosition(b2Vec2(x,y));
    itemsId+=1;
    this->dynamic_objs.push_back(ptr);
    createAndAddFixture(this->dynamic_objs.back().get(), 60.0f/PTM, 60.0f/PTM, 0, TILE, SENSOR, false);
    if (this->dynamic_objs.size() > MAX_AMOUNT_OBJECTS*std::max(1,(int)cars.size()/2)){
        world.DestroyBody(this->dynamic_objs.front().get()->getBody());
        this->dynamic_objs.pop_front(); // I remove the first one, life cycle over.
    }
}

void GameWorld::_explodeIfOutOfBounds(RaceCar &car){
    auto pos = car.getPosition();
    bool out_bounds = (pos.x < -5 || pos.x > map.width/PTM) || (pos.y < -5 || pos.y > map.width/PTM);
    if (out_bounds){
        car.takeDamage(car.car_stats.hp);
    }
}

void GameWorld::_loadXYInRoad(int& x, int& y){
    int tilesRoad = this->road_positions.size();
    //Random
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tilesRoad - 1);
    int pos = dis(gen);

    int rx = rand()%(int)PTM_TILE - PTM_TILE/2;
    int ry = rand()%(int)PTM_TILE - PTM_TILE/2;;
    auto it1 = std::next(this->road_positions.begin(), pos);
    x = (int) (std::round(it1->x) + rx*.8);
    y = (int) (std::round(it1->y) + ry*.8);
}

// TODO: If we dont use them, remove tileType as parameter
void GameWorld::createOffRoad(int x, int y, int tileType) {
    b2Body* newBody = makeNewBody(world, b2_staticBody, x, y);
    this->offroad_bodies.emplace_back("offroad", newBody);
    createAndAddFixture(&(this->offroad_bodies.back()), PTM_TILE, PTM_TILE, 0, TILE, SENSOR, false);
}

void GameWorld::createExtras(int x, int y, int tileType) {
    b2Body* newBody = makeNewBody(world, b2_staticBody, x, y);
    auto ptr = std::make_shared<Entity>(newBody);
    this->static_objs.push_back(ptr);
    createAndAddFixture(this->static_objs.back().get(), PTM_TILE, PTM_TILE, 0, OBSTACLE, PLAYER, false);
}

int GameWorld::createCar(InfoBlock carStats) {
    auto fpos = finishingLine->getPosition();
    int size = cars.size();
    int y = fpos.y - (0.1f + (int)(1+cars.size()/2))*CAR_HEIGHT/PTM;
    int x = fpos.x - CAR_WIDTH/PTM + (2*CAR_WIDTH/PTM)*(size%2);
    b2Body* newBody = makeNewBody(world, b2_dynamicBody,x,y);
    int carId = size;
    cars.emplace_back(carId, carStats, newBody);
    newBody->SetBullet(true);

    createAndAddFixture(&(cars.back()),1,2,1,PLAYER, 0, false);
    createAndAddFixture(&(cars.back()), (float)CAR_WIDTH/PTM, (float)CAR_HEIGHT/PTM,0,PLAYER, PLAYER|OBSTACLE, false);
    createAndAddFixture(&(cars.back()),(float)CAR_WIDTH/PTM, (float)CAR_HEIGHT/PTM,0,SENSOR, TILE, true);

    auto ptr = std::shared_ptr<StatusEffect>(new LapCooldown(10, true));
    cars.back().addEffect(ptr);
    return carId;
}

void GameWorld::createFinishingLine(int x, int y) {
    b2Body* newBody = makeNewBody(world, b2_staticBody, x, y);
    finishingLine = std::make_shared<FinishingLine>(newBody);
    createAndAddFixture(finishingLine.get(),PTM_TILE,(float)FINISH_LINE_HEIGHT/PTM,0,TILE, SENSOR, false);
}

void GameWorld::respawnCar(RaceCar &car) {
    auto f = [&](){
        std::cout<<"a car is respawning"<<std::endl;
        car.car_stats.hp = car.car_stats.base_hp;
        auto fpos = finishingLine->getPosition();
        int y = fpos.y - 1.1f *CAR_HEIGHT/PTM;
        int x = fpos.x;
        car.getBody()->SetTransform(b2Vec2(x,y),0);
        auto ptr = std::shared_ptr<StatusEffect>(new LapCooldown(15,true));
        car.addEffect(ptr);
    };
    auto ptr = std::shared_ptr<StatusEffect>(new CallbackStatusEffect("RESPAWN", f, 5));
    car.addEffect(ptr);
    std::cout<<"a car died"<<std::endl;
}

void GameWorld::attempItemSpawn() {
    int randomTime = rand() % (TIME_TO_ITEMS - TIME_FROM_ITEMS + 1) + TIME_FROM_ITEMS;
    if ( (int) this->timeModifiers > randomTime*.5){
        std::cout << "We generate random item\n";
        _createItem();
        this->timeModifiers = 0;
    } else if (this->timeModifiers > TIME_TO_ITEMS)
        this->timeModifiers = 0;
}

void GameWorld::stepItems() {
    auto it = dynamic_objs.begin();
    while(it != dynamic_objs.end()){
        if (!it->get()->enabled){
            world.DestroyBody(it->get()->getBody());
            it = dynamic_objs.erase(it);
        } else {
            auto v = it->get()->dirToTarget();
            it->get()->getBody()->SetLinearVelocity(100.0*v);
            it++;
        }
    }
}
