#include "Map.hpp"

void Map::gener(){
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

std::vector<float> Map::getBordandFood(){
    std::vector<float> answ(16);
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

    return answ;
}
