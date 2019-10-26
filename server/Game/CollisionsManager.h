

#ifndef MICROMACHINES_COLLISIONSMANAGER_H
#define MICROMACHINES_COLLISIONSMANAGER_H

#include "Box2D/Box2D.h"
#include "RaceCar.h"
#include "Tile.h"
#include <map>

enum _entityCategory {
    TILE = 0x0001,
    MODIFS = 0x0002,
    PLAYER = 0x0004,
    SENSOR = 0x0008
};

struct carMods{
    double delay;
    double duration;
    int stacks;
    RaceCar* car;
    void (*f)(RaceCar&);
};

class CollisionsManager : b2ContactListener {
    std::map<std::string, carMods> delayed_effects;
public:
    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

    void step(double timestep){};

};


#endif //MICROMACHINES_COLLISIONSMANAGER_H
