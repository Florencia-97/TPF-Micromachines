#ifndef MICROMACHINES_MAPSLAYER_H
#define MICROMACHINES_MAPSLAYER_H

#include <string>
#include <vector>

class MapsLayer {
    void _loadMap(const std::string &mapPath, std::string& key, std::vector<std::vector<int>>& matrix);
    void _loadHW(const std::string &mapPath);
public:
    std::vector<std::vector<int>> ground;
    std::vector<std::vector<int>> road;
    std::vector<std::vector<int>> extras;
    int width;
    int height;
    MapsLayer(const std::string& mapPath);
};


#endif //MICROMACHINES_MAPSLAYER_H
