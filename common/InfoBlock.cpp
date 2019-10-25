#include "InfoBlock.h"

InfoBlock::InfoBlock(const std::string &init, bool fromFile) {
    this->src_yaml = YAML::Load(init);
}

std::string InfoBlock::getString(const std::string key) {
    return src_yaml[key].as<std::string>();
}

int InfoBlock::getInt(const std::string key) {
    return src_yaml[key].as<int>();
}

float InfoBlock::getFloat(const std::string key) {
    return src_yaml[key].as<float>();
}

std::list<int> getList(std::string key){
    //Implement me
    std::list<int> list;
    return list;
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
