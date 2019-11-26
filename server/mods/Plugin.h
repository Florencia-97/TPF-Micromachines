#ifndef PLUGIN_H
#define PLUGIN_H

#include <vector>
#include "../Game/entities/CarStats.h"

class Plugin {
protected:
    double side_length_;
public:
    Plugin() : side_length_(0) {}
    virtual void modifyCars(std::vector<CarStats*>& cars) {
        return;
    }

    virtual bool createItem() {
        return false;
    }
    virtual ~Plugin() {}
};

// the types of the class factories
typedef Plugin* create_t();
typedef void destroy_t(Plugin*);

#endif
