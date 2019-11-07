

#include "CollisionsManager.h"


void CollisionsManager::BeginContact(b2Contact *contact) {
    auto entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
    entityA->resolveCollision(entityB);
    entityB->resolveCollision(entityA);
}

void CollisionsManager::EndContact(b2Contact *contact) {
    auto entityA = (Entity*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto entityB = (Entity*)contact->GetFixtureB()->GetBody()->GetUserData();
    entityA->endContact(entityB);
    entityB->endContact(entityA);
}
