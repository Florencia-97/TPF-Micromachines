#ifndef _CONFIGURACION_
#define _CONFIGURACION_

#include <bits/stdc++.h>
#include <map>

class fileConfigurationNotFound : public std::exception {
    virtual const char* what() const throw() {
        std::string error = "Configuration file wasnt found,";
        error += " check if your file path name is right\n";
        return error.c_str();
    }
};

class Configuration{
    void _loadConfigs();

    public:
    std::map<std::string, float> configs;
    Configuration();
};

#endif