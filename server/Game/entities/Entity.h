

#ifndef MICROMACHINES_ENTITY_H
#define MICROMACHINES_ENTITY_H

#include <Game/status_effects/StatusEffect.h>
#include "Box2D/Box2D.h"
#include <list>


//probably make this one a virtual class
class Entity {
    int y_size;
    int x_size;
    int id;
    int tileId;
    //std::string stats;

protected:
    b2Body* body;
    b2Vec2 target;
public:
    bool enabled;

    //only supports making objects with a square bounding box
    explicit Entity(b2Body* &newbody);

    Entity(b2Body* &newbody, int id, const int tile);

    virtual void resolveCollision(Entity *collidedWith){};

    virtual void endContact(Entity *wasTouching){};

    virtual bool addEffect(std::shared_ptr<StatusEffect> &newStatusEffect){return false;};

    virtual void removeEffect(std::string effectId){};

    virtual bool isPlayer(){return false;};

    void setTargetPosition(b2Vec2 pos){target = pos;};

    b2Vec2 dirToTarget(){
        auto v = (target - getPosition());
        std::cout<<v.Length()<<std::endl;
        if (v.Length() < .8f) return {0,0};
        v.Normalize();
        return v; 
    };

    b2Vec2 getPosition();

    b2Vec2 getSize();

    float32 getAngle();

    void loadPosToInfoBlock(InfoBlock& ib, int cont);

    void attachFixture(b2FixtureDef &boxFixtureDef);

    b2Body *getBody();
};


#endif //MICROMACHINES_ENTITY_H
