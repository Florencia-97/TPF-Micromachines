#ifndef _CONFIGURACION_
#define _CONFIGURACION_

#include <bits/stdc++.h>
#include <vector>
#include <map>

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
    std::map<std::string, std::map<std::string, float>> carsConfigs;

    public:
    float getDataFromCar(std::string car, std::string field);
    float getConfigurationData(std::string conf);
    Configuration();
};

#endif