
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


class GameWorld {
    b2World world;
    MapsLayer map;
    CollisionsManager cl;
    std::shared_ptr<FinishingLine> finishingLine;

    std::list<RaceCar> cars;
    std::list<OffRoad> road_bodies;

    //static instances are those which  will remain in place
    std::list<std::shared_ptr<Entity>> static_objs;
    //Dynamic Instances are those which come and go from the field, (ie items)
    std::list<std::shared_ptr<Entity>> dynamic_objs;
    void _createItem();
    float timeModifiers;

public:
    //POS creates a world with no gravity for top-down action
    GameWorld();
    int createCar(InfoBlock carStats);
    void processEvent(int id, InfoBlock &event);
    RaceCar& getCar(int id);
    void loadWorld(std::string);
    InfoBlock status();

    //POS advances the simulation and all instances within one timestep
    void Step(float timeStep);
    void createRoad(int x, int y, int tileId); //yaml &stats?
    void createExtras(int x, int y, int tileId);

    void createFinishingLine(int x, int y);
};


#endif //MICROMACHINES_GAMEWORLD_H
