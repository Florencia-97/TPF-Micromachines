#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <string>
#include "PluginLibrary.h"

// this goes away! just to show how plugins work
// g++ --std=c++11 -rdynamic PluginLoader.cpp PluginLibrary.cpp main.cpp -o main -ldl
int main() {
    const char* path1 = "../../plugins/pluginOne.so";
    const char* path2 = "../../plugins/pluginTwo.so";
    std::string path = "../../plugins";
    PluginLibrary pluginLibrary(path);
    pluginLibrary.runPlugins();
//    PluginLoader pluginOne(path1);
//    std::vector<int> cars = {1,2,3,4};
//    pluginOne.plugin->modifyCars(cars);
//    for (size_t i = 0; i < cars.size(); ++i){
//        std::cout << cars[i] << std::endl;
//    }
//    PluginLoader pluginTwo(path2);
//    pluginTwo.plugin->modifyWorld(cars);
//    for (size_t i = 0; i < cars.size(); ++i) {
//        std::cout << cars[i] << std::endl;
//    }
}
