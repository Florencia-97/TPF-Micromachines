
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
#include <Game/entities/PhysicalRoad.h>


class GameWorld {
    b2World world;
    MapsLayer map;
    CollisionsManager cl;
    std::list<RaceCar> cars;
    std::list<PhysicalRoad> road_bodies;
    float timeModifiers;

    //Dynamic Instances are those which come and go from the field, (ie items)
    std::list<Entity> dynamic_objs;
    void _createItem();

public:
    //POS creates a world with no gravity for top-down action
    GameWorld();
    int createCar(InfoBlock carStats);
    void processEvent(int car_id, InfoBlock event);
    RaceCar& getCar(int id);
    void loadWorld(std::string);
    InfoBlock status();

    //POS advances the simulation and all instances within one timestep
    void Step(float timestep);
    void createRoad(int x, int y, int tileId); //yaml &stats?
};


#endif //MICROMACHINES_GAMEWORLD_H
