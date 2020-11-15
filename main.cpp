#include "GA.hpp"
#include <iostream>
//#include "MathModel\Header\Game.h"
#define BREAK
int main(){  

    
    int size;
    std::vector<int> layerSize;
    std::cout<<"Enter the number of hidden layer: ";
    std::cin>>size;
    size+=2;
    layerSize.resize(size);
    layerSize[0] = 16;
    for (int i = 1; i < size-1; i++)
    {
        std::cout<<"\nEnter size layer number "<<i<<": ";
        std::cin>>layerSize[i];
    }
    layerSize[size-1] = 4;
    float cross;
    float mut ;
    int maxgen ;
    int pop;
    std::cout<<"\nEnter population: ";
    std::cin>>pop;
    std::cout<<"\nEnter crossover chance(0,1): ";
    std::cin>>cross;
    std::cout<<"\nEnter nutation chance (0,1): ";
    std::cin>>mut;
    std::cout<<"\nEnter max generation (Enter 0 if you want max gen): ";
    std::cin>>maxgen;

    std::cout<<"Start GA:\n";
    GA test(layerSize, pop,cross,mut,maxgen);
    test.CreateFullMaps();
    test.run();
    //Game game(1, 1 , 20,20);
    
    return 0;
}