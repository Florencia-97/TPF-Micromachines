#include <string>
#include <vector>
#include <iostream>

#include "LuaWrapper.h"


int main ( int argc, char *argv[] )
{
    LuaWrapper lw;
    std::vector<std::vector<int>> iv = {{1,2,3}, {4,5,6}, {7,8,9}};
    int x = 3;
    int y = 5;
    std::string des = lw.getDesition(iv, x, y);
    std::cout << des << std::endl;
	return 0;
}
