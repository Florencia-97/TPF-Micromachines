#ifndef MICROMACHINES_ITEMROCK_H
#define MICROMACHINES_ITEMROCK_H

#include "../Entity.h"

// Reduces life and speed
class ItemRock : Entity {
public:
    explicit ItemRock(b2Body* &newBody) : Entity(newBody){};
};


#endif //MICROMACHINES_ITEMROCK_H
