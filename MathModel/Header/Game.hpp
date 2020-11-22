#pragma once
#include "../Header/Snake.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>

class Game{
public:
    Game(int n, int high, int width);
    Game(int n, int r, int high,int width);
    ~Game();



    void Logic();
    void Drow();
    void Input(std::vector<std::vector<float>> x);
    void Input(std::vector<int> x);

    void newFood(int num);//NEED UPGRADE THIS FUNCTION
    void generateCurrentFood(int index);

    std::vector<float> getScan(int num);

    bool checkBorder(int x, int y);
    bool checkFood(int x, int y);
    bool checkSnake(int x, int y);
    bool checkEnemy(int x, int y,int num);
    bool checkHead(int x, int y, int num);
    
//  function for study and save

    void SaveGame(std::vector<int*> rr, std::vector<int**> F, std::vector<std::vector<int>> scanData);

    int getNumAlive();
    int getMaxStep();

    void emptyMap();

//  bool operator==(const std::vector<int>& left, const std::vector<int>& right);
    private:
    std::vector<Snake> snake;
    int radius;
    int numofSnake;
    int high;
    int width;
    std::vector<std::vector<int>> border;
    std::vector<std::vector<int>> food;
    int numofAlive;
};