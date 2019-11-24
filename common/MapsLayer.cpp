#include "yaml-cpp/yaml.h"
#include "MapsLayer.h"

void MapsLayer::_loadMap(const std::string &mapPath, std::string& key, std::vector<std::vector<int>>& matrix) {
    YAML::Node config = YAML::LoadFile(mapPath);
    YAML::Node mapYaml = config[key];

    int num = 1;
    for (YAML::iterator it = mapYaml.begin(); it != mapYaml.end(); ++it) {
        const YAML::Node &row = *it;
        std::vector<int> rowVector;
        std::string numberRow = std::to_string(num);
        YAML::Node column = row[numberRow];
        for (YAML::iterator c = column.begin(); c != column.end(); ++c) {
            const YAML::Node &col_value = *c;
            int tileNumber = col_value.as<int>();
            rowVector.push_back(tileNumber);
        }
        matrix.push_back(rowVector);
        num++;
    }
}

void MapsLayer::_loadHW(const std::string &mapPath){
    YAML::Node config = YAML::LoadFile(mapPath);
    YAML::Node mapYaml = config["Config"];

    YAML::Node h = mapYaml["h"];
    YAML::Node w = mapYaml["w"];

    this->width = w.as<int>();
    this->height = h.as<int>();
}

MapsLayer::MapsLayer(const std::string& mapPath) {
    load(mapPath);
}

void MapsLayer::load(const std::string &mapPath) {
    std::string ground = "Ground";
    std::string road = "Road";
    std::string extras = "Extras";
    _loadMap(mapPath, ground, this->ground);
    _loadMap(mapPath, road,this->road);
    _loadMap(mapPath, extras ,this->extras);
    _loadHW(mapPath);
}
