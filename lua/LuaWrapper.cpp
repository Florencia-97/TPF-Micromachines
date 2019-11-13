#include <vector>
#include <iostream>
#include "LuaWrapper.h"

LuaWrapper::LuaWrapper(){
    this->L = luaL_newstate();
    luaL_openlibs(L);
}

template <typename T, typename U>
void asTable(lua_State* L, T begin, U end) {
    lua_newtable(L);
    for (size_t i = 0; begin != end; ++begin, ++i) {
        lua_pushinteger(L, i + 1);
        lua_pushnumber(L, *begin);
        lua_settable(L, -3);
    }
}

std::string LuaWrapper::decide_move(std::vector<int>& v1){
    std::string des;
    lua_getglobal(L, "decide_move");

    asTable(L, v1.begin(), v1.end());

    /* call the function with 2 arguments, return 1 result */
    lua_call(L, 1, 1);

    /* get the result */
    des = (std::string)lua_tostring(L, -1);
    lua_pop(L, 1);

    return des;
}

std::string LuaWrapper::getDesition(std::vector<int>& iv){
    luaL_dofile(this->L, "lua/fake_player.lua");

    /* call the add function */
    std::string des = decide_move(iv);

    /* print the result */
    std::cout << des << std::endl;
}

LuaWrapper::~LuaWrapper(){
    lua_close(this->L);
}