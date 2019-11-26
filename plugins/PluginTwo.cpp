#include "../server/mods/Plugin.h"
#include <cmath>
#include <vector>
#include <iostream>

// This plugin boost cars speed with 5

// g++ --std=c++11 -fPIC -rdynamic -shared -o ./pluginTwo.so ./PluginTwo.cpp
class PluginTwo : public Plugin {
public:
    virtual void modifyCars(std::vector<CarStats*>& cars) override {
        for (size_t i = 0; i < cars.size(); ++i){
            cars[i]->max_speed += 5;
        }
    }

    virtual bool createItem() override {
        // It creates a random item
        return true;
    }
};

// the class factories
extern "C" Plugin* create() {
    return new PluginTwo;
}
extern "C" void destroy(Plugin* p) {
    delete p;
}

