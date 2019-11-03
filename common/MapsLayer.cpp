#include <iostream>
#include "yaml-cpp/yaml.h"
#include "MapsLayer.h"

std::vector<std::vector<int>> _loadMap(const std::string &mapPath, std::string& key) {
    YAML::Node config = YAML::LoadFile(mapPath);
    YAML::Node mapYaml = config[key];
    std::vector<std::vector<int>> matrix;

    int num = 0;
    for (YAML::iterator it = mapYaml.begin(); it != mapYaml.end(); ++it) {
        const YAML::Node &row = *it;
        std::vector<int> rowVector;
        std::string numberRow = std::to_string(num);
        YAML::Node column = row[numberRow];
        for (YAML::iterator c = column.begin(); c != column.end(); ++c) {
            const YAML::Node &col_value = *c;
            int tileNumber = col_value.as<int>();
            std::cout << tileNumber << std::endl;
            rowVector.push_back(tileNumber);
        }
        matrix.push_back(rowVector);
        num++;
    }

}

std::vector<std::vector<int>> MapsLayer::getLayerN(std::string& mapPath, int n){
    std::string layer = "";
    if (n == 0) layer = "Lower";
    else if (n == 1) layer = "Map";
    else if (n==2) layer = "Upper";
    else {
        std::cout << "No layer with that number!" << std::endl;
    }
    return _loadMap(mapPath, layer);
}