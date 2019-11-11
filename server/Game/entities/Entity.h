

#ifndef MICROMACHINES_ENTITY_H
#define MICROMACHINES_ENTITY_H

#include <Game/status_effects/StatusEffect.h>
#include "Box2D/Box2D.h"
#include <list>


//probably make this one a virtual class
class Entity {
    bool enabled;
    int y_size;
    int x_size;
    int id;
    //std::string stats;

protected:
    b2Body* body;
public:
    //only supports making objects with a square bounding box
    Entity(b2Body* &newbody);

    Entity(b2Body* &newbody, int id);

    virtual void resolveCollision(Entity *collidedWith){};

    virtual void endContact(Entity *wasTouching){};

    virtual bool addEffect(std::shared_ptr<StatusEffect> &newStatusEffect){return false;};

    virtual void removeEffect(std::string effectId){};

    b2Vec2 getPosition();

    b2Vec2 getSize();

    float32 getAngle();

    void loadPosToInfoBlock(InfoBlock& ib, int cont);

    void attachFixture(b2FixtureDef &boxFixtureDef);

    b2Body *getBody();
};


#endif //MICROMACHINES_ENTITY_H
