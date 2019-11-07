#include "PluginLoader.h"
#include <dlfcn.h>
#include <string>

PluginLoader::PluginLoader(const char* path) {
    this->pluginRef = dlopen(path, RTLD_LAZY);
    if (!this->pluginRef) {
        std::cerr << "Cannot load library: " << dlerror() << '\n';
    }
    dlerror();

    create_t* create_plugin = (create_t*) dlsym(this->pluginRef, "create");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
    }
    this->plugin = create_plugin();
}

PluginLoader::~PluginLoader() {
    destroy_t* destroy_plugin = (destroy_t*) dlsym(this->pluginRef, "destroy");
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
    } else{
        destroy_plugin(this->plugin);
    }
    dlclose(this->pluginRef);
}