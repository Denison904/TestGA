#include "Map.hpp"

void Map::gener(int r){
    map.resize(r);
    int count = 0;
    do
    {
        for (int j = 0; j < 8; j++)
        {
            map[j] = rand()%2 -1;
        }
        if(map[1]==-1) count++;
        if(map[3]==-1) count++;
        if(map[4]==-1) count++;
        if(map[6]==-1) count++;
    } while (count<4);
}

std::vector<double> Map::getBordandFood(){
    
    std::vector<double> answ;
    #ifndef TREATENT

    answ.resize(8);
    for (int i = 0; i < answ.size(); i++)
    {
        answ[i]=map[i];
    }
    

    #endif
    #ifdef TREATENT
    answ.resize(16);
    for(int i = 0 ; i < 8; i++){
        if(map[i]==-1){
            answ[i] = 1;
        }else{
            answ[i] = 0;
        }
        if(map[i]==1){
            answ[i+8] = 1;
        }else{
            answ[i+8] = 0;
        }
    }
    #endif
    return answ;
}

bool operator==(const Map &left , const Map &right){
    if(left.map.size()!=right.map.size())
        return false;
    for (int i = 0; i < left.map.size(); i++)
    {
        if(left.map[i] != right.map[i])
            return false;
    }
    
    return true;
}



bool Map::Check() {

    int  count = 0;

    if (map[1] == -1) count++;
    if (map[3] == -1) count++;
    if (map[4] == -1) count++;
    if (map[6] == -1) count++;
    if (count == 4) {
        return false;
    }
    return true;
   
}