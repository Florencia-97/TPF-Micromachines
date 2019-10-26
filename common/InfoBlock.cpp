

#include "InfoBlock.h"
#include <iostream>

void InfoBlock::Load(const std::string &init, bool fromFile) {
    if (!fromFile) {
        this->src_yaml = YAML::Load(init);
    } else {
        try {
            this->src_yaml = YAML::LoadFile(init);
        } catch (std::runtime_error e) {
            std::cerr <<  e.what() << HERE << std::endl;
        }
    }
}

InfoBlock::InfoBlock(const std::string &init, bool fromFile) {
    this->Load(init, fromFile);
}

std::string InfoBlock::getString(const std::string key) {
    return get<std::string>(key);
}

int InfoBlock::getInt(const std::string key) {
    return get<int>(key);
}

float InfoBlock::getFloat(const std::string key) {
    return get<float>(key);
}


bool InfoBlock::exists(std::string key){
    try{
        return src_yaml[key] && src_yaml[key] != nullptr;
    } catch (...) {
        return false;
    }
}

std::string InfoBlock::srcString() {
    std::string s = "{";
    for(YAML::iterator i = src_yaml.begin(); i != src_yaml.end(); i++){
        s += i->first.as<std::string>() + ": " + i->second.as<std::string>() + ", ";
    }
    s.substr(0, s.size()- 3);
    s += "}";
    return s;
}

InfoBlock InfoBlock::getNestedInfo(std::string key) {
    return InfoBlock(this->getString(key), true);
}
