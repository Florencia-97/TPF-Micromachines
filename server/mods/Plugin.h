#ifndef PLUGIN_H
#define PLUGIN_H

#include <vector>

class Plugin {
protected:
    double side_length_;
public:
    Plugin() : side_length_(0) {}
    virtual ~Plugin() {}
    void set_side_length(double side_length) {
        return;
    }
    //virtual void modifyCars(std::vector<int> cars);
    virtual void modifyCars(std::vector<int>& cars) {
        return;
    }

    virtual void modifyWorld(std::vector<int>& world) {
        return;
    }
};

// the types of the class factories
typedef Plugin* create_t();
typedef void destroy_t(Plugin*);

#endif
