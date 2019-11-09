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
        std::vector<int> vectorCar;
        //List
        for (YAML::iterator l = list.begin(); l != list.end(); ++l) {
            const YAML::Node &list_value = *l;
            int value = list_value.as<int>();
            vectorCar.push_back(value);
        }
        this->carsConfigs.insert({carName, vectorCar});
    }
    std::cout << "Cars configuration loaded correctly\n" << std::endl;
}

InfoBlock Configuration::getDataFromCar(std::string& car){
    InfoBlock ib;
    std::vector<int> carConfig =  this->carsConfigs[car];
    for(std::size_t i=0; i<carConfig.size(); ++i){
        if (i == 0) ib[HEALTH] = carConfig[i];
        else if (i == 1) ib[MAX_SPEED] = carConfig[i];
        else if (i == 2) ib[ACCELERATION] = carConfig[i];
        else if (i == 3) ib[ROTATION_FORCE] = carConfig[i];
    }
    ib[CAR_TYPE] = car;
    return ib;
}

float Configuration::getConfigurationData(std::string conf){
	return this->configs[conf];
}