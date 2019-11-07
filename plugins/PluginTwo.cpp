#include "../server/mods/Plugin.h"
#include <cmath>
#include <vector>
#include <iostream>

// TODO: change names.
// g++ --std=c++11 -fPIC -rdynamic -shared -o ./pluginTwo.so ./PluginTwo.cpp

class PluginTwo : public Plugin {
public:
    virtual void modifyWorld(std::vector<int>& world) override {
        for (size_t i = 0; i < world.size(); ++i){
            std::cout << world[i] << std::endl;
        }
    }
};

// the class factories
extern "C" Plugin* create() {
    return new PluginTwo;
}
extern "C" void destroy(Plugin* p) {
    delete p;
}
