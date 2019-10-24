

#ifndef MICROMACHINES_GAMEOBJECT_H
#define MICROMACHINES_GAMEOBJECT_H

#include "Box2D/Box2D.h"

#define STATIC_OBJ 1
#define DYNAMIC_OBJ 2
#define PLAYER 3

//probably make this one a virtual class
class GameObject {
    bool enabled;
    b2Body* body;
    int y_size;
    int x_size;
    int type;
    //std::string stats;

public:

    //only supports making objects with a square bounding box
    GameObject(int type, b2Body* &newbody, int xSize, int ySize);

    virtual void resolveCollision(b2Fixture &collidedWith);

    b2Vec2 getPosition();

    b2Vec2 getSize();
};


#endif //MICROMACHINES_GAMEOBJECT_H
