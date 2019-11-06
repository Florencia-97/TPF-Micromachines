#include "../server/mods/Plugin.h"
#include <cmath>
#include <vector>
#include <iostream>

// TODO: change names.
// g++ --std=c++11 -fPIC -rdynamic -shared -o ./pluginTwo.so ./PluginTwo.cpp

class PluginOne : public Plugin {
public:
    virtual void modifyWorld(std::vector<int>& world) override {
        for (size_t i = 0; i < world.size(); ++i){
            world[i] += 1;
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
