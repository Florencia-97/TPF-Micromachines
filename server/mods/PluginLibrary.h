#ifndef MICROMACHINES_PLUGINLIBRARY_H
#define MICROMACHINES_PLUGINLIBRARY_H

#include <vector>
#include <dirent.h>
#include <string>
#include "PluginLoader.h"

class PluginLibrary {
    std::vector<PluginLoader*> plugins;
public:
    explicit PluginLibrary(const char* path);
    void runPlugins();
    ~PluginLibrary();
};


#endif //MICROMACHINES_PLUGINLIBRARY_H
