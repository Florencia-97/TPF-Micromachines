#include "../server/mods/Plugin.h"
#include <cmath>
#include <vector>
#include <iostream>

// TODO: change names.
// g++ --std=c++11 -fPIC -rdynamic -shared -o ./pluginOne.so ./PluginOne.cpp

class PluginOne : public Plugin {
public:
    virtual void modifyCars(std::vector<int>& cars) override {
        for (size_t i = 0; i < cars.size(); ++i){
            cars[i] += 1;
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
