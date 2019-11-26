
#ifndef MICROMACHINES_GAMEWORLD_H
#define MICROMACHINES_GAMEWORLD_H

#include "Box2D/Box2D.h"
#include <vector>
#include "Game/entities/Entity.h"
#include "Game/entities/RaceCar.h"
#include "CollisionsManager.h"
#include "../common/MapsLayer.h"
#include "../config/tileConstants.h"
#include <chrono>
#include <thread>
#include <Game/entities/OffRoad.h>
#include "Game/entities/FinishingLine.h"


struct Coordinate{
    float x = 0;
    float y = 0;
};

class GameWorld {
    b2World world;
    MapsLayer map;
    CollisionsManager cl;
    std::shared_ptr<FinishingLine> finishingLine;

    std::list<OffRoad> offroad_bodies;
    std::list<Coordinate> road_positions;

    //Static instances are those which  will remain in place
    std::list<std::shared_ptr<Entity>> static_objs;

    //Dynamic Instances are those which come and go from the field, (ie items)
    std::list<std::shared_ptr<Entity>> dynamic_objs;

    float timeModifiers;
    int itemsId;

    void _createItem();
    //loads a random position from a random road to x & y
    void _loadXYInRoad(int&x, int&y);
    void _explodeIfOutOfBounds(RaceCar &car);
    //creates a physical representation of an off road section of the map
    void createOffRoad(int x, int y, int tileId);
    void createExtras(int x, int y, int tileId);
    void createFinishingLine(int x, int y);
    void respawnCar(RaceCar &car);
    void attempItemSpawn();
    //removes all items marked as consumed
    void stepItems();

public:
    //list of all cars currently in the game
    std::list<RaceCar> cars;

    //POS creates a world with no gravity for top-down action
    GameWorld();

    //PRE carStats must contain the keys ACCELERATION, HEALTH, ROTATION_FORCE & MAX_SPEED
    //creates a car and returns the new car's id
    int createCar(InfoBlock carStats);

    //Processes a keyPressed/released event sent from client
    //PRE if the keys ACTION_TYPE or ACTION_TYPE_DOWN exist in event they
    //must contain one of the following values UP, DOWN, LEFT, RIGHT
    void processEvent(int id, InfoBlock &keyPressed);

    //PRE id must be valid
    //POS returns a reference to the car with the id
    RaceCar& getCar(int id);

    //loads the world from file, map_name must be a valid name of a map stored in a file
    void loadWorld(std::string map_name);

    //returns positions and statuses of all dynamic (cars & items) objects in the world
    //at the moment of calling
    InfoBlock status();

    //POS advances the simulation one timestep
    void Step(float timeStep);

};


#endif //MICROMACHINES_GAMEWORLD_H
