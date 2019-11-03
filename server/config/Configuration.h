#ifndef _CONFIGURACION_
#define _CONFIGURACION_

#include <bits/stdc++.h>
#include <vector>
#include <map>
#include "../../common/infostream/InfoBlock.h"

class fileConfigurationNotFound : public std::exception {
    virtual const char* what() const throw() {
        std::string error = "Configuration file wasn't found,";
        error += " check if your file path name is right\n";
        return error.c_str();
    }
};

class Configuration{
    void _loadServerConfigs(std::string path);
    void _loadCarsConfigs(std::string path);
    std::map<std::string, float> configs;
    std::map<std::string, std::vector<int>> carsConfigs;

    public:
    InfoBlock getDataFromCar(std::string& car);
    float getConfigurationData(std::string conf);
    Configuration();
};

#endif