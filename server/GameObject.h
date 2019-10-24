

#ifndef MICROMACHINES_GAMEOBJECT_H
#define MICROMACHINES_GAMEOBJECT_H

#include "Box2D/Box2D.h"

enum _entityCategory {
    STATIC_OBJ = 0x0001,
    DYNAMIC_OBJ = 0x0002,
    PLAYER = 0x0004,
    ROAD_SENSOR = 0x0008,
    ROAD = 0x00016,
    GRASS = 0x00032,
    BONUSES = 0x00064
};

//probably make this one a virtual class
class GameObject {
    bool enabled;
    b2Body* body;
    int y_size;
    int x_size;
    uint16 type;
    //std::string stats;

public:

    //only supports making objects with a square bounding box
    GameObject(uint16 type, b2Body* &newbody);

    virtual void resolveCollision(b2Fixture &collidedWith);

    b2Vec2 getPosition();

    b2Vec2 getSize();

    float32 getAngle();

    void attachFixture(b2FixtureDef &boxFixtureDef);
};


#endif //MICROMACHINES_GAMEOBJECT_H
