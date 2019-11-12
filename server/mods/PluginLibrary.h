#ifndef MICROMACHINES_PLUGINLIBRARY_H
#define MICROMACHINES_PLUGINLIBRARY_H

#include <vector>
#include <dirent.h>
#include <string>
#include <list>
#include <Game/entities/RaceCar.h>
#include "PluginLoader.h"
#include "../../common/conc/BaseThread.h"

class PluginLibrary : public BaseThread{
    const char* path;
    std::list<RaceCar>* cars;
    void _run() override;
public:
    explicit PluginLibrary(const char* p);
    void loadCars(std::list<RaceCar>* cars);
    void runPlugins(std::vector<PluginLoader*>& plugins);
    void loadPlugins(std::vector<PluginLoader*>& plugins);
};


#endif //MICROMACHINES_PLUGINLIBRARY_H
