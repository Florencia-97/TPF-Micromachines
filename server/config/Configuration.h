#ifndef _CONFIGURACION_
#define _CONFIGURACION_

#include <bits/stdc++.h>
#include <map>

// Maybe i dont need it because of yaml error
class fileConfigurationNotFound : public std::exception {
    virtual const char* what() const throw() {
        std::string error = "Configuration file wasnt found,";
        error += " check if your file path name is right\n";
        return error.c_str();
    }
};

class Configuration{
    void _loadConfigs(std::string path);
    std::map<std::string, float> configs;

    public:
    float getConfigurationData(std::string conf);
    Configuration();
    Configuration(std::string path);
};

#endif