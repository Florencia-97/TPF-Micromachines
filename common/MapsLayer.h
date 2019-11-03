#ifndef MICROMACHINES_MAPSLAYER_H
#define MICROMACHINES_MAPSLAYER_H

#include <string>
#include <vector>

class MapsLayer {
public:
    static std::vector<std::vector<int>> getLayerN(std::string& mapPath, int n);
};


#endif //MICROMACHINES_MAPSLAYER_H
