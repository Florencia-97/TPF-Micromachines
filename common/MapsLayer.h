#ifndef MICROMACHINES_MAPSLAYER_H
#define MICROMACHINES_MAPSLAYER_H

#include <string>
#include <vector>

#define TILE_SIZE 512

class MapsLayer {
    void _loadMap(const std::string &mapPath, std::string& key, std::vector<std::vector<int>>& matrix);
    void _loadHW(const std::string &mapPath);
public:
    std::vector<std::vector<int>> ground;
    std::vector<std::vector<int>> road;
    std::vector<std::vector<int>> extras;
    int width;
    int height;

    //create an unloaded map
    MapsLayer() = default;

    //PRE can only be called once to load an unloaded map
    void load(const std::string& mapPath);

    //create and load a map (calls load())
    explicit MapsLayer(const std::string& mapPath);
};


#endif //MICROMACHINES_MAPSLAYER_H
