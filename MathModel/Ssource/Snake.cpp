#include "../header/Snake.h"

Snake::Snake(int n, int x, int y){
    body =4;
    number = n;
    for (int i = 0; i < body; i++)
    {
        TailX.push_back(x+i);
        TailY.push_back(y);
    }
    alive =true;
    hungry = 100;
    course = 0;
}

void Snake::setTailX(int x){
    TailX.push_back(x);
}

void Snake::setTailY(int y){
    TailY.push_back(y);
}

void Snake::setAlive(){
    alive = false;
}

void Snake::setBody(){
    body++;
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
    for (int i = body-1; i >0; i--)
    {
        TailY[i]= TailY[i-1];
        TailX[i]= TailX[i-1];
    }
    TailX[0] +=x;
    TailY[0] +=y;
}

int Snake::getTailX(int index){
    return TailX[index];
}

int Snake::getTailY(int index){
    return TailY[index];
}

int Snake::getBody(){
    return body;
}

bool Snake::getAlive(){
    return alive; 
}

int Snake::getNumber(){
    return number;
}

int Snake::getHungry(){
    return hungry;
}

int Snake::getCourse(){
    return course;
}