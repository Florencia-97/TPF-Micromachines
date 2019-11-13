#ifndef MICROMACHINES_LUAWRAPPER_H
#define MICROMACHINES_LUAWRAPPER_H

#include <string>
#include "../lua53/src/lua.hpp"

class LuaWrapper {
    lua_State* L;
    std::string decide_move(std::vector<int>& v1);
public:
    LuaWrapper();
    std::string getDesition(std::vector<int>& iv);
    ~LuaWrapper();
};


#endif //MICROMACHINES_LUAWRAPPER_H
