#include <vector>
#include "LuaWrapper.h"

LuaWrapper::LuaWrapper(){
    this->L = luaL_newstate();
    luaL_openlibs(L);
}

//template <typename T, typename U>
//void asTable(lua_State* L, T begin, U end) {
//    lua_newtable(L);
//    for (size_t i = 0; begin != end; ++begin, ++i) {
//        lua_pushinteger(L, i + 1);
//        lua_pushnumber(L, *begin);
//        lua_settable(L, -3);
//    }
//}

void asMatrix(lua_State* L, std::vector<std::vector<int>>& iv) {
    lua_createtable(L, iv.size(), 0);
    for (size_t i = 0; i != iv.size(); ++i) {
        lua_pushnumber(L, i + 1);
        std::vector<int> cv = iv[i];
        lua_createtable(L, cv.size(),0);
        for (size_t j = 0; j != cv.size(); ++j) {
            lua_pushinteger(L, j + 1);
            lua_pushnumber(L, cv[j]);
            lua_settable(L, -3);
        }
        lua_settable(L, -3);
    }
}

std::string LuaWrapper::decide_move(std::vector<std::vector<int>>& v1, int x, int y, int r, int lm){
    std::string des;
    lua_getglobal(L, "decide_move");

    asMatrix(L,v1);
    lua_pushnumber(L, x);
    lua_pushnumber(L, y);
    lua_pushnumber(L, r);
    lua_pushnumber(L, lm);

    /* Call the function with 5 arguments, return 1 result */
    lua_call(L, 5, 1);

    /* get the result, is a string */
    des = (std::string)lua_tostring(L, -1);
    lua_pop(L, 1);

    return des;
}

std::string LuaWrapper::getDesition(std::vector<std::vector<int>>& iv, int x, int y, int r, int lm){
    luaL_dofile(this->L, "client/ia/lua/fake_player.lua");
    std::string des = decide_move(iv, x, y, r,lm);
    return des;
}

LuaWrapper::~LuaWrapper(){
    lua_close(this->L);
}