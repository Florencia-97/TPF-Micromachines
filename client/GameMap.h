#ifndef MICROMACHINES_GAMEMAP_H
#define MICROMACHINES_GAMEMAP_H
#include <vector>
#include "tiles/Tile.h"
#include "yaml-cpp/yaml.h"
#include "tiles/TilesFactory.h"

class GameMap {
    TilesFactory tiles_factory;
    std::vector<std::vector<std::shared_ptr<Tile>>> map;
    std::vector<std::vector<std::shared_ptr<Tile>>> ground;
    std::vector<std::vector<std::shared_ptr<Tile>>> road;
    std::vector<std::vector<std::shared_ptr<Tile>>> extras;

  /*Loads a complete layer.
   * PRE: The matrix must represent a complete layer of elements that will be
   * used for the creation of the map. Therefore, each of the layers used
   * should have the same size*/
    void _loadLayer(std::vector<std::vector<int>> layerMatrix,
				  SDL_Renderer *gRenderer, const std::string &mapName);
public:
    int width;
    int height;

    /*Loads the map named "map". In order to do thar, the map must have a
    * layer "ground", "road" and "extras"*/
    void loadMap(const std::string &map, SDL_Renderer *gRenderer);

    /*Renders the map
    * POST: The order of the layers is Ground->Road->Extras*/
    void render(SDL_Rect &camera, SDL_Renderer *renderer);

    /*Renders the decoration of the map*/
    void renderDeco(SDL_Rect &camera, SDL_Renderer *renderer, int xoffset,
            int yoffset);
  /*Cleans the four vectors in the class*/
  void clear();
};

#endif //MICROMACHINES_GAMEMAP_H
