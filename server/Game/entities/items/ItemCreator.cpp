#include <memory>
#include <random>
#include <Game/entities/Entity.h>
#include "ItemCreator.h"
#include "../../../../config/constants.h"
#include "ItemBoost.h"
#include "ItemRock.h"

std::shared_ptr<Entity> ItemCreator::createItem(b2Body* newBody){
    //Random id between 0 and the amount of items.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, ITEMS_AMOUNT - 1);
    int id = dis(gen);
    auto item = nullptr;

//    switch (id){
//        case ITEM_BOOST:
//            item = std::shared_ptr<Entity>(new ItemBoost(newBody));
//            break;
//        case ITEM_ROCK:
//            item = std::shared_ptr<Entity>(new ItemRock(newBody));
//            break;
//        case ITEM_OIL:
//            item = std::shared_ptr<Entity>(new ItemBoost(newBody));
//            break;
//        case ITEM_MUD:
//            item = std::shared_ptr<Entity>(new ItemBoost(newBody));
//            break;
//        case ITEM_HEALTH:
//            item = std::shared_ptr<Entity>(new ItemBoost(newBody));
//            break;
//        default:
//            item = std::shared_ptr<Entity>(new ItemBoost(newBody));
//            break;
//    }
    return item;
}