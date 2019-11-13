#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "../lua53/src/lua.hpp"


/* the Lua interpreter */
lua_State* L;

template <typename T, typename U>
void as_table(lua_State* L, T begin, U end) {
    lua_newtable(L);
    for (size_t i = 0; begin != end; ++begin, ++i) {
        lua_pushinteger(L, i + 1);
        lua_pushnumber(L, *begin);
        lua_settable(L, -3);
    }
}

std::string luaadd (std::vector<int>& v1){
	std::string sum;

	/* the function name */
	lua_getglobal(L, "decide_move");

	as_table(L, v1.begin(), v1.end());

	/* call the function with 2 arguments, return 1 result */
	lua_call(L, 1, 1);

	/* get the result */
	sum = (std::string)lua_tostring(L, -1);
	lua_pop(L, 1);

	return sum;
}

int main ( int argc, char *argv[] )
{
	std::string des;

	/* initialize Lua */
	L = luaL_newstate();

	/* load Lua base libraries */
	luaL_openlibs(L);

	std::vector<int> iv = {1,2,3,4};
	/* load the script */
	luaL_dofile(L, "lua/fake_player.lua");

	/* call the add function */
	des = luaadd(iv);

	/* print the result */
	std::cout << des << std::endl;

	/* cleanup Lua */
	lua_close(L);


	return 0;
}
