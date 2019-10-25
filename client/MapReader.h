#ifndef _MAPREADER_
#define _MAPREADER_

#include <list>
#include <string>

class MapReader {
    //Creates a matrix that represents the arena in order to draw it
    public:
    std::list<std::list<int>> createMap(std::string arenaPath);
};

#endif
