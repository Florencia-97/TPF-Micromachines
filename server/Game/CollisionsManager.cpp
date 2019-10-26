

#include "CollisionsManager.h"

namespace {
    bool sortFixtures(b2Fixture* &a, b2Fixture* &b){
        if (a->GetFilterData().categoryBits & SENSOR){
            return true;//already sorted
        } else if(b->GetFilterData().categoryBits & SENSOR) {
            auto c = a;
            a = b;
            b = c;
            return true;
        }
        return false;
    }
}

void CollisionsManager::BeginContact(b2Contact *contact) {
    b2Fixture* sensorFixture = contact->GetFixtureA();
    b2Fixture* objectFixture = contact->GetFixtureB();
    bool r = sortFixtures(sensorFixture, objectFixture);
    if (!r) return; //I dont care about these collisions
    auto car = (RaceCar*)sensorFixture->GetUserData();
    
    //replace with case
    if (! objectFixture->GetFilterData().categoryBits & TILE) return;
    std::string key = std::to_string(TILE)+ "&" + std::to_string(car->id);
    if (delayed_effects.find(key) != delayed_effects.end()){

    } else {

    }
}

void CollisionsManager::EndContact(b2Contact *contact) {
    b2ContactListener::EndContact(contact);
}
