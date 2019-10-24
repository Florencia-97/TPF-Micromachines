
#ifndef MICROMACHINES_GAMEWORLD_H
#define MICROMACHINES_GAMEWORLD_H

#include "Box2D/Box2D.h"
#include <vector>
#include "GameObject.h"

class GameWorld {
    b2World world;
    //CollisionDetector cd;
    //std::vector<Car> cars;

    //objects which are a static part of the map background
    std::vector<GameObject> background_objs;

    //Dynamic Instances are those which come and go from the field, (ie items)
    //std::vector<GameObject> dynamic_objs;

public:

    //POS creates a world with no gravity for top-down action
    GameWorld() : world(b2Vec2(0,0)){};

    /*
      &Car createCar(yaml &carStats);

      &GameObject createDynamicObject(yaml &stats?);

      void Step();

     */

    void createBackgroundObject(); //yaml &stats?
};


#endif //MICROMACHINES_GAMEWORLD_H
