#include <string>
#include <vector>

#include "LuaWrapper.h"


int main ( int argc, char *argv[] )
{
    LuaWrapper lw;
    std::vector<int> iv = {1,2,3,4};
    std::string des = lw.getDesition(iv);
	return 0;
}
