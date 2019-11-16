#include <memory>
#include <random>
#include "ItemCreator.h"
#include "../../../../config/constants.h"
#include "ItemBoost.h"
#include "ItemRock.h"
#include "ItemHealth.h"
#include "ItemMud.h"
#include "ItemOil.h"

std::shared_ptr<Entity> ItemCreator::createItem(b2Body* newBody, int itemsId){
    //Random id between 0 and the amount of items.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, ITEMS_AMOUNT - 1);
    int id = dis(gen);

    std::cout << id << std::endl;

    switch (id){
        case ITEM_BOOST:
            return std::make_shared<ItemBoost>(newBody, itemsId);
        case ITEM_ROCK:
            return std::make_shared<ItemRock>(newBody, itemsId);
        case ITEM_OIL:
            return std::make_shared<ItemOil>(newBody, itemsId);
        case ITEM_MUD:
            return std::make_shared<ItemMud>(newBody, itemsId);
        case ITEM_HEALTH:
            return std::make_shared<ItemHealth>(newBody, itemsId);
        default:
            return std::make_shared<ItemRock>(newBody, itemsId);
    }
}