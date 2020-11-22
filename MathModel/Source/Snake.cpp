#include "../Header/Snake.hpp"

Snake::Snake(int x, int y){
    for (int i = 0; i < 4; i++)
    {
        TailX.push_back(x+i);
        TailY.push_back(y);
    }
    alive =true;
    hungry = 100;
    course = 0;
    step = 0;
    point =0 ;
}

void Snake::setTail(int x, int y){
    TailX.push_back(x);
    TailY.push_back(y);
}

void Snake::setStep(){
    this->step++;
}

void Snake::setAlive(){
    alive = false;
}

void Snake::setPoint(){
    this->point++;
}

void Snake::setHungry(){
    hungry--;
}

void Snake::setHungry(int x){
    hungry = x;   
}

void Snake::setFullHungry(){
    hungry=100;
}

void Snake::setCourse(int x){
    course = x;
}

void Snake::setMove(int x, int y){
  //  int tmpX = TailX[0], tmpY = TailY[0];
    for (int i = TailX.size()-1; i >0; i--)
    {
        TailY[i]= TailY[i-1];
        TailX[i]= TailX[i-1];
    }
    TailX[0] +=x;
    TailY[0] +=y;
}


int Snake::getPoint(){
    return this->point;
}

int Snake::getStep(){
    return this->step;
}

int Snake::getTailX(int index){
    return TailX[index];
}

int Snake::getTailY(int index){
    return TailY[index];
}

int Snake::getBody(){
    return this->TailX.size();
}

bool Snake::getAlive(){
    return alive; 
}


int Snake::getHungry(){
    return hungry;
}

int Snake::getCourse(){
    return course;
}

