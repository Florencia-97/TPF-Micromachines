

#ifndef MICROMACHINES_COLLISIONDETECTOR_H
#define MICROMACHINES_COLLISIONDETECTOR_H

#include "Box2D/Box2D.h"

enum _entityCategory {
    TILE = 0x0001,
    MODIFS = 0x0002,
    PLAYER = 0x0004,
    SENSOR = 0x0008
};

class CollisionDetector : b2ContactListener {
    void BeginContact(b2Contact* contact) override{};

    void EndContact(b2Contact* contact) override{};
};


#endif //MICROMACHINES_COLLISIONDETECTOR_H
