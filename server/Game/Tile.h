

#ifndef MICROMACHINES_TILE_H
#define MICROMACHINES_TILE_H

#include "Entity.h"
#include "../../common/InfoBlock.h"

class Tile : public Entity {
public:
    InfoBlock stats;

    Tile(InfoBlock stats, b2Body* body) : Entity(body), stats(std::move(stats)){};

    //void resolveCollision(b2Fixture &collidedWith) override;
};


#endif //MICROMACHINES_TILE_H
