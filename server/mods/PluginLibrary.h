#ifndef MICROMACHINES_PLUGINLIBRARY_H
#define MICROMACHINES_PLUGINLIBRARY_H

#include <vector>
#include <dirent.h>
#include <string>
#include <list>
#include <Game/entities/RaceCar.h>
#include <server/Game/GameWorld.h>
#include "PluginLoader.h"
#include "../../common/conc/BaseThread.h"

class PluginLibrary{
    const char* path;
    std::list<RaceCar>* cars;
    std::vector<PluginLoader*> plugins;
    float clock;
    void _runPlugins(GameWorld* game);
    void _loadPlugins();
public:
    explicit PluginLibrary(const char* p);
    void loadCars(std::list<RaceCar>* cars);
    void runPlugins(float timestep, GameWorld* game);
    ~PluginLibrary();
};


#endif //MICROMACHINES_PLUGINLIBRARY_H
