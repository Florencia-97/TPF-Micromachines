

#ifndef MICROMACHINES_TILE_H
#define MICROMACHINES_TILE_H

#include "GameObject.h"
#include "../../common/InfoBlock.h"

class Tile : public GameObject {
public:
    InfoBlock stats;

    Tile(InfoBlock stats, b2Body* body) : GameObject(body), stats(std::move(stats)){};

    //void resolveCollision(b2Fixture &collidedWith) override;
};


#endif //MICROMACHINES_TILE_H
