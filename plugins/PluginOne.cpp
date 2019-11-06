#include "../server/mods/Plugin.h"
#include <cmath>
#include <vector>
#include <iostream>

class PluginOne : public Plugin {
public:
    virtual void modifyCars(std::vector<int>& cars) const {
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
