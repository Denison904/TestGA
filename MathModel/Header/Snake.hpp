#pragma once
#include <vector>

class Snake{
    public:
    Snake(){};
    Snake( int x, int y);
    
    void setTail(int x, int y);
    void setStep();
    void setAlive();
    void setPoint();
    void setHungry();
    void setHungry(int x);
    void setFullHungry();
    void setCourse(int x);
    void setMove(int x, int y);

    int getPoint();
    int getStep();
    int getTailX(int index);
    int getTailY(int index);
    int getBody();
    bool getAlive();
    int getNumber();
    int getHungry();
    int getCourse();
    
    bool checkHeadTail();

    private:
    std::vector<int> TailX;
    std::vector<int> TailY;
    bool alive;
    int hungry;
    int step;
    int course;
    int point;
};