#include <string>

#include "Event.h"

Event::Event(std::string& action): actionName(action) {}

std::string Event::toYamlString(){
    //Just an example
    std::string yaml = "{ " + this->actionName + "}";
    return yaml;
}

Event::~Event(){}