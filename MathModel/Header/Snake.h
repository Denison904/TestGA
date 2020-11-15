#pragma once
#include <vector>

class Snake{
    public:
    Snake(){};
    Snake(int n, int x, int y);
    
    void setTailX(int x);
    void setTailY(int y);
    void setAlive();
    void setBody();
    void setHungry();
    void setHungry(int x);
    void setFullHungry();
    void setCourse(int x);
    void setMove(int x, int y);


    int getTailX(int index);
    int getTailY(int index);
    int getBody();
    bool getAlive();
    int getNumber();
    int getHungry();
    int getCourse();
    

    private:
    std::vector<int> TailX;
    std::vector<int> TailY;
    int body;
    bool alive;
    int number;   
    int hungry;
    int course;
};