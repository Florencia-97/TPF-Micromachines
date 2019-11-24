#ifndef MICROMACHINES_TILESFACTORY_H
#define MICROMACHINES_TILESFACTORY_H

#include "Tile.h"
#include "../rendering/TextureLoader.h"
#include "../../common/infostream/InfoBlock.h"

class TilesFactory {
  InfoBlock ib;
  TextureLoader tLoader;
 public:

  /*Constructor of the class TileFactory. This class will create the Tiles
   * needed for the map*/
  TilesFactory();

  /*This method uses the tyleType value for creating a new Tile.
   * PRE: tyleType must respect the convention established in the constants.h
   * file
   * POS: this function returns a pointer to the created Tile. This tile, will
   * have the position X and Y*/
  std::shared_ptr<Tile> get_tile(int tyleType, int x, int y,
								 SDL_Renderer *gRenderer);

  /*Destroyer of the class*/
  ~TilesFactory();
};

#endif //MICROMACHINES_TILESFACTORY_H
