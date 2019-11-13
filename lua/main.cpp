#include <string>
#include <vector>
#include <iostream>

#include "LuaWrapper.h"
#include "../common/MapsLayer.h"


int main ( int argc, char *argv[] )
{
    LuaWrapper lw;
    MapsLayer mapsLayer("maps/race_1.yaml");
    int x = 3;
    int y = 5;
    std::cout << "Ground\n";
    std::string des = lw.getDesition(mapsLayer.ground, x, y);
    std::cout << des << std::endl;

    x = 10;
    y  = 32;
    std::cout << "Road\n";
    des = lw.getDesition(mapsLayer.road, x, y);
    std::cout << des << std::endl;

    x = 10;
    y  = 32;
    std::cout << "Extras\n";
    des = lw.getDesition(mapsLayer.extras, x, y);
    std::cout << des << std::endl;
	return 0;
}
