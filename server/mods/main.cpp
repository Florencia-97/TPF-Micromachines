#include "Plugin.h"
#include "PluginLoader.h"
#include <iostream>
#include <dlfcn.h>
#include <vector>

int main() {
    const char* path = "../../plugins/pluginOne.so";
    PluginLoader pluginLoader(path);
    std::vector<int> cars = {1,2,3,4};
    pluginLoader.plugin->modifyCars(cars);
    for (size_t i = 0; i < cars.size(); ++i){
        std::cout << cars[i] << std::endl;
    }
}
