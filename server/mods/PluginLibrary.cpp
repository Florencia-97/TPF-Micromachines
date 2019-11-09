#include "PluginLibrary.h"
#include <string>

PluginLibrary::PluginLibrary(const char* path) {
    // Loads all plugins .so in plugins folder
    // TODO: leaking memory when created in gameThread, why??
    if (auto dir = opendir(path)) {
        while (auto f = readdir(dir)) {
            if (f->d_name[0] == '.') continue;
            std::string fileName = f->d_name;
            std::string pathName = path;
            if (fileName.find(".so") != std::string::npos){
                fileName =  pathName + "/" + fileName;
                auto plugin = new PluginLoader(fileName.c_str());
                this->plugins.push_back(plugin);
            }
        }
        closedir(dir);
    }
}

void PluginLibrary::runPlugins(){
    std::vector<CarStats> cars;
    std::cout << "run plugins\n";
    for (size_t i=0; i< plugins.size(); ++i){
        plugins[i]->plugin->modifyCars(cars);
        plugins[i]->plugin->modifyWorld(cars);
    }
}

PluginLibrary::~PluginLibrary() {
    for (auto it = plugins.begin(); it != plugins.end(); ++it){
        delete(*it);
    }
}