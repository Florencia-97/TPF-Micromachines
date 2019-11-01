//
// Created by flox on 30/10/19.
//

#ifndef MICROMACHINES_TILESFACTORY_H
#define MICROMACHINES_TILESFACTORY_H

#include "Tile.h"
#include "../rendering/TextureLoader.h"
#include "../../common/infostream/InfoBlock.h"

/*
 * Returns the desired tile by its id
*/

class TilesFactory {
    InfoBlock ib;
    TextureLoader tLoader;
public:
    TilesFactory();
    std::shared_ptr<Tile> getTile(int tyleType, int x, int y, SDL_Renderer *gRenderer);
    ~TilesFactory();
};


#endif //MICROMACHINES_TILESFACTORY_H
