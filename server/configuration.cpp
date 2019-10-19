#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include "yaml-cpp/yaml.h"

#include "configuration.h"

Configuration::Configuration() {
	this->_loadConfigs();
}

void Configuration::_loadConfigs(){
    //Adding try and catch in here?
	YAML::Node file = YAML::LoadFile("config/configuration_server.yaml");
	if (file.IsNull()){
		throw fileConfigurationNotFound();
	}
	float max_car_speed = file["max_car_speed"].as<float>();
    this->configs.insert({"max_car_speed", max_car_speed});
	std::cout << "Server configuration loaded correctly!\n" << std::endl;
}
