#ifndef _MAPREADER_
#define _MAPREADER_

#include <list>
#include <string>

//Creates a matrix that represents the arena in order to draw it
class MapReader {
    std::list<std::list<int>> matrix;

    public:
    MapReader(std::string& arenaPath);
    std::list<std::list<int>> getMatrix();
    ~MapReader();
};

#endif
