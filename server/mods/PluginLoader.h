#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "Plugin.h"
#include <string>
#include <iostream>
#include <dlfcn.h>

class PluginLoader {
    void* pluginRef;
public:
    Plugin* plugin;
    PluginLoader(const char* path);
    ~PluginLoader();
};

#endif