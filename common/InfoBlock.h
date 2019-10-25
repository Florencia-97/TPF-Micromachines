

#ifndef MICROMACHINES_INFOBLOCK_H
#define MICROMACHINES_INFOBLOCK_H

#include "yaml-cpp/yaml.h"

class InfoBlock {
public:
    YAML::Node src_yaml;

    explicit InfoBlock(const std::string &init, bool fromFile);

    std::string getString(std::string key);

    int getInt(std::string key);

    float getFloat(std::string key);

    std::list<int> getList(std::string key);

    std::string srcString();

    template <class T>
    T get(std::string key){
        return this->src_yaml[key].as<T>();
    }

};


#endif //MICROMACHINES_INFOBLOCK_H
