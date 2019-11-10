#ifndef MICROMACHINES_ITEMBOOST_H
#define MICROMACHINES_ITEMBOOST_H

#include "../Entity.h"

// Increase in car speed
class ItemBoost : Entity{
public:
    explicit ItemBoost(b2Body* &newBody) : Entity(newBody){};
};


#endif //MICROMACHINES_ITEMBOOST_H
