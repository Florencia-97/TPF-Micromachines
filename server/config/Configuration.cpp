#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include "yaml-cpp/yaml.h"

#include "Configuration.h"

Configuration::Configuration() {
	this->_loadConfigs();
}

void Configuration::_loadConfigs(){
    //Adding try and catch in here?
	YAML::Node file = YAML::LoadFile("config/configuration_server.yaml");
	if (file.IsNull()){
		throw fileConfigurationNotFound();
	}
	// Saving in map all configurations in yaml file
	for(YAML::const_iterator it=file.begin();it!=file.end();++it) {
		this->configs.insert({it->first.as<std::string>(), it->second.as<float>()});
	}
	std::cout << "Server configuration loaded correctly!\n" << std::endl;
}
