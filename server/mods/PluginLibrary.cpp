#include "PluginLibrary.h"
#include <string>

PluginLibrary::PluginLibrary(const char* path) {
    // TODO: leaking memory when created in gameThread, why??
    this->path = path;
}

void PluginLibrary::runPlugins(std::vector<PluginLoader*>& plugins){
    std::vector<CarStats> cars;
    for (size_t i=0; i< plugins.size(); ++i){
        plugins[i]->plugin->modifyCars(cars);
        plugins[i]->plugin->modifyWorld(cars);
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
        this->sleep(10); // TODO: constant, time between plugins run
    }
    std::cout << "Plugin library stops running\n";
}