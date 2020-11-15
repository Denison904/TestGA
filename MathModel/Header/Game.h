#pragma once
#include "../header/Snake.h"
#include <iostream>
#include <fstream>
#include <ctime>

class Game{
public:
    Game(int n, int high, int width);
    Game(int n, int r, int high,int width);
    ~Game();

    void Test(){
        int x = 5, y = 5;
        snake = new Snake[1];
        snake[0] = Snake(0,5,5);
        if(checkSnake(x ,y )){
            std::cout<<"Y\n";
        }else{
            std::cout<<"N\n";
        }
    }

    void Logic();
    void Drow();
    void Input(std::vector<std::vector<int>> x);
    void Input(std::vector<int> x);

    void newFood(int num);//NEED UPGRADE THIS FUNCTION
    void generateCurrentFood(int index);

    std::vector<int> getScan(int num);

    bool checkBorder(int x, int y);
    bool checkFood(int x, int y);
    bool checkSnake(int x, int y);
    bool checkEnemy(int x, int y,int num);
    bool checkHead(int x, int y, int num);
    
//  function for study and save

    void SaveGame(std::vector<int*> rr, std::vector<int**> F, std::vector<std::vector<int>> scanData);

    int getNumAlive();



//  bool operator==(const std::vector<int>& left, const std::vector<int>& right);
    private:
    Snake* snake;
    int radius;
    int *scan;
    int numofSnake;
    int high;
    int width;
    int** border;
    int numofBorder = 0;
    int numofFood;
    int** food;
    int numofAlive = 1 ;
    std::vector<int> step;
};