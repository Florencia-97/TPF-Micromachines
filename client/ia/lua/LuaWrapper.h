#ifndef MICROMACHINES_LUAWRAPPER_H
#define MICROMACHINES_LUAWRAPPER_H

#include <string>
#include "../lua53/src/lua.hpp"

class LuaWrapper {
    lua_State* L;
    std::string decide_move(std::vector<std::vector<int>>& v1, int x, int y, int r, int lm);
public:
    LuaWrapper();
    std::string getDesition(std::vector<std::vector<int>>& iv, int x, int y, int r, int lm);
    ~LuaWrapper();
};


#endif //MICROMACHINES_LUAWRAPPER_H
