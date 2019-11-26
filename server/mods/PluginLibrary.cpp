#include "PluginLibrary.h"
#include <string>
#include "../config/constants.h"

PluginLibrary::PluginLibrary(const char* path): clock(0.0) {
    this->path = path;
    this->cars = nullptr;
    _loadPlugins();
}

void PluginLibrary::loadCars(std::list<RaceCar>* cars){
    this->cars = cars;
    std::cout << "Cars Loaded\n";
}

void PluginLibrary::_runPlugins(GameWorld* game){
    std::vector<CarStats*> carsStats;
    for (auto & car : *cars){
        carsStats.push_back(&car.car_stats);
    }
    for (auto & plugin : plugins){
        plugin->plugin->modifyCars(carsStats);
        if (plugin->plugin->createItem()){
            std::cout << "Plugin creates random item\n";
            game->_createItem();
        }
    }
}

void PluginLibrary::_loadPlugins(){
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

void PluginLibrary::runPlugins(float timeStep, GameWorld* game) {
    if (this->clock < TIME_BETWEEN_PLUGINS){
        this->clock += timeStep;
        return;
    }
    std::cout << "Running plugins\n";
    _runPlugins(game);
    this->clock = 0.0;
    std::cout << "Waiting for plugins to reactivate again!\n";
}

PluginLibrary::~PluginLibrary() {
    for (auto & plugin : plugins){
        delete(plugin);
    }
}