#pragma once
#include <vector>
#include <vector>

class Map{
public:
    std::vector<int> map;
    Map(){};
    void gener(int r);
    bool Check();
    std::vector<double> getBordandFood();
    friend bool operator==(const Map &left , const Map &right);
};