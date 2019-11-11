#ifndef MICROMACHINES_ITEMCREATOR_H
#define MICROMACHINES_ITEMCREATOR_H

#include "../Entity.h"

class ItemCreator {
public:
    static std::shared_ptr<Entity> createItem(b2Body* newBody, int itemsId);
};


#endif //MICROMACHINES_ITEMCREATOR_H
