#ifndef MICROMACHINES_ITEMCREATOR_H
#define MICROMACHINES_ITEMCREATOR_H

// TODO: maybe this is a static method.
class ItemCreator {
public:
    std::shared_ptr<Entity> createItem(b2Body* newBody);
};


#endif //MICROMACHINES_ITEMCREATOR_H
