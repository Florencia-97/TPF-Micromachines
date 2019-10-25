
#ifndef MICROMACHINES_GAMEWORLD_H
#define MICROMACHINES_GAMEWORLD_H

#include "Box2D/Box2D.h"
#include <vector>
#include "GameObject.h"
#include "RaceCar.h"

enum _entityCategory {
    STATIC_OBJ = 0x0001,
    DYNAMIC_OBJ = 0x0002,
    PLAYER = 0x0004,
    ROAD_SENSOR = 0x0008,
    ROAD = 0x00016,
    GRASS = 0x00032,
    BONUSES = 0x00064
};

class GameWorld {
    b2World world;
    //CollisionDetector cd;
    std::vector<RaceCar> cars;

    //objects which are a static part of the map background
    std::vector<GameObject> background_objs;

    //Dynamic Instances are those which come and go from the field, (ie items)
    //std::vector<GameObject> dynamic_objs;

public:

    //POS creates a world with no gravity for top-down action
    GameWorld();


      int createCar(std::string &carStats);

      RaceCar& getCar(int id);
    /*
      &GameObject createDynamicObject(yaml &stats?);

     */

    //POS advances the simulation and all instances within one timestep
    void Step();

    void createBackgroundObject(); //yaml &stats?
};


#endif //MICROMACHINES_GAMEWORLD_H
