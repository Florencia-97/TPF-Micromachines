#include "../server/mods/Plugin.h"
#include <cmath>
#include <vector>
#include <iostream>

// TODO: change names.
// ../server/Game/status_effects/StatusEffect.cpp
// g++ --std=c++11 -fPIC -rdynamic -shared -o ./pluginOne.so ./PluginOne.cpp

class PluginOne : public Plugin {
public:
    virtual void modifyCars(std::vector<CarStats>& cars) override {
        for (size_t i = 0; i < cars.size(); ++i){
            //std::cout << cars[i].max_speed << std::endl;
            //std::cout << cars[i] << std::endl;
        }
    }
};

// the class factories
extern "C" Plugin* create() {
    return new PluginOne;
}
extern "C" void destroy(Plugin* p) {
    delete p;
}
