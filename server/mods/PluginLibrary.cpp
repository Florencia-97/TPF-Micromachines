#include "PluginLibrary.h"
#include <string>
#include "../config/constants.h"

PluginLibrary::PluginLibrary(const char* path): clock(0.0) {
    this->path = path;
    this->cars = nullptr;
    _loadPlugins(plugins);
}

void PluginLibrary::loadCars(std::list<RaceCar>* cars){
    this->cars = cars;
    std::cout << "Cars Loaded\n";
}

void PluginLibrary::_runPlugins(std::vector<PluginLoader*>& plugins){
    std::vector<CarStats*> carsStats;
    for (auto & car : *cars){
        carsStats.push_back(&car.car_stats);
    }
    for (auto & plugin : plugins){
        plugin->plugin->modifyCars(carsStats);
        plugin->plugin->modifyWorld(carsStats);
    }
}

void PluginLibrary::_loadPlugins(std::vector<PluginLoader*>& plugins){
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

void PluginLibrary::runPlugins(float timestep) {
    if (this->clock < TIME_BETWEEN_PLUGINS){
        this->clock += timestep;
        return;
    }
    std::cout << "Running plugins\n";
    _runPlugins(plugins);
    this->clock = 0.0;
    std::cout << "Waiting for plugins to reactivate again!\n";
}

PluginLibrary::~PluginLibrary() {
    std::cout << "Deleting plugins\n";
    for (auto & plugin : plugins){
        delete(plugin);
    }
}