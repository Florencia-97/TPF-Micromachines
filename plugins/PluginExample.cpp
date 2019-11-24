#include "../server/mods/Plugin.h"
#include <cmath>
#include <vector>
#include <iostream>

// When your plugin is ready, just compile it running this in your terminal
// (Be sure to be in the right foldier)
// g++ --std=c++11 -fPIC -rdynamic -shared -o ./pluginExample.so ./PluginExample.cpp

class PluginExample : public Plugin {
public:
    virtual void modifyCars(std::vector<CarStats*>& cars) override {
        // Here goes you code , modify carStats to your wish
        // For example, if you want to raise everyones health 5 points
        // you should do: cars[i]->hp += 5;
    }
};

// This must not be modified, just change plugin class name :)
extern "C" Plugin* create() {
    return new PluginExample;
}
extern "C" void destroy(Plugin* p) {
    delete p;
}
