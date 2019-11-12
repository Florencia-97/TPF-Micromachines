#include "PluginLibrary.h"
#include <string>

PluginLibrary::PluginLibrary(const char* path) {
    this->path = path;
    this->cars = nullptr;
}

void PluginLibrary::loadCars(std::list<RaceCar>* cars){
    this->cars = cars;
}

void PluginLibrary::runPlugins(std::vector<PluginLoader*>& plugins){
    std::vector<CarStats*> carsStats;
    for (auto & car : *cars){
        carsStats.push_back(&car.car_stats);
    }
    for (auto & plugin : plugins){
        plugin->plugin->modifyCars(carsStats);
        plugin->plugin->modifyWorld(carsStats);
    }
}

void PluginLibrary::loadPlugins(std::vector<PluginLoader*>& plugins){
    if (auto dir = opendir(path)) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] == '.') continue;
            std::string fileName = f->d_name;
            std::string pathName = path;
            if (fileName.find(".so") != std::string::npos){
                fileName =  pathName + "/" + fileName;
                auto plugin = new PluginLoader(fileName.c_str());
                plugins.push_back(plugin);
            }
        }
        closedir(dir);
    }
}

void PluginLibrary::_run() {
    while (this->isAlive()){
        std::cout << "Fetching and running plugins\n";
        std::vector<PluginLoader*> plugins;
        loadPlugins(plugins);
        runPlugins(plugins);
        for (auto it = plugins.begin(); it != plugins.end(); ++it){
            delete(*it);
        }
        std::cout << "Waiting for plugins to reactivate again!\n";
        this->sleep(15); // TODO: constant, time between plugins run
    }
    std::cout << "Plugin library stops running, able to quit\n";
}