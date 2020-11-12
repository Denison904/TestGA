#pragma once
#include <vector>


class Map{
public:
    int map[8];
    Map(){};
    void gener();
    std::vector<float> getBordandFood();
};