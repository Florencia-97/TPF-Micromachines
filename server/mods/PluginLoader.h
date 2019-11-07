#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "Plugin.h"
#include <string>
#include <iostream>

class PluginLoader {
    void* pluginRef;
public:
    Plugin* plugin;
    explicit PluginLoader(const char* path);
    ~PluginLoader();
};

#endif