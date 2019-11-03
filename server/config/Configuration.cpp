#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include "yaml-cpp/yaml.h"

#include "Configuration.h"
#include "../../config/constants.h"

Configuration::Configuration() {
    this->_loadCarsConfigs("config/cars_configuration.yaml");
    this->_loadServerConfigs("config/configuration_server.yaml");
}

void Configuration::_loadServerConfigs(std::string path){
    YAML::Node serverConfigsFile = YAML::LoadFile(path);
    if (serverConfigsFile.IsNull()){
        throw fileConfigurationNotFound();
    }

    for (YAML::const_iterator it=serverConfigsFile.begin();it!=serverConfigsFile.end();++it) {
        this->configs.insert({it->first.as<std::string>(), it->second.as<float>()});
    }
    std::cout << "Server configuration loaded correctly!\n" << std::endl;
}

void Configuration::_loadCarsConfigs(std::string path){
    YAML::Node carsConfigFile = YAML::LoadFile(path);

    if (carsConfigFile.IsNull()){
        throw fileConfigurationNotFound();
    }
    for (YAML::iterator it = carsConfigFile.begin(); it != carsConfigFile.end(); ++it) {
        std::string carName = it->first.as<std::string>();
        YAML::Node &list = it->second;
        std::map<std::string, float> mapCar;
        //List
        for (YAML::iterator l = list.begin(); l != list.end(); ++l) {
            int cont;
            const YAML::Node &list_value = *l;
            float value = list_value.as<float>();
            if (cont == 0) mapCar.insert({ HEALTH, value});
            else if (cont == 1) mapCar.insert({ MAX_SPEED, value});
            else if (cont == 2) mapCar.insert({ ACELERATION, value});
            else if (cont == 3) mapCar.insert({ ROTATION_MAX, value});
            cont++;
        }
        this->carsConfigs.insert({carName, mapCar});
    }
    std::cout << "Cars configuration loaded correctly\n" << std::endl;
}

InfoBlock Configuration::getDataFromCar(std::string car){
    InfoBlock ib;
    std::map<std::string, float> carConfig =  this->carsConfigs[car];
    for (auto const& it : carConfig){
        ib[it.first] = it.second;
    }
    return ib;

}

float Configuration::getConfigurationData(std::string conf){
	return this->configs[conf];
}