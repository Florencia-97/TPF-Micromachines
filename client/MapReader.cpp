
#include "MapReader.h"
#include <iostream>
#include "../common/infostream/InfoBlock.h"
#include "yaml-cpp/yaml.h"

MapReader::MapReader(std::string& arenaPath){
    YAML::Node config = YAML::LoadFile(arenaPath);
    YAML::Node map = config["Map"];
    int num = 1;
    for (YAML::iterator it = map.begin(); it != map.end(); ++it) {
        const YAML::Node& row = *it;
        std::string numberRow = std::to_string(num);
        std::list<int> list;
        YAML::Node column = row[numberRow];
        for (YAML::iterator c = column.begin(); c != column.end(); ++c) {
            const YAML::Node& col = *c;
            list.push_back(col.as<int>());
        }
        this->matrix.push_back(list);
        num += 1;
    }
    std::cout << "Loaded!\n";
}

std::list<std::list<int>> MapReader::getMatrix(){
    return this->matrix;
}

MapReader::~MapReader() {}

//Afterwards we can return the h and w of the arena if it is needed

