#ifndef MICROMACHINES_EVENT_H
#define MICROMACHINES_EVENT_H

#include <string>

class Event {
    std::string actionName; // We have to see
public:
    Event(std::string& action);
    ~Event();
};


#endif //MICROMACHINES_EVENT_H
