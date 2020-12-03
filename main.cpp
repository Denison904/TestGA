#define BREAK

#include "GA.hpp"
#include <string>
#include <iostream>
#include <ctime>
#include "MathModel\Header\Game.hpp"

int main(){ 

    int size;
    std::vector<int> layerSize;
    std::cout<<"Enter the number of hidden layer: ";
    std::cin>>size;
    size+=2;
    layerSize.resize(size);
    layerSize[0] = 8;//WARNING!
    for (int i = 1; i < size-1; i++)
    {
        std::cout<<"\nEnter size layer number "<<i<<": ";
        std::cin>>layerSize[i];
    }
    layerSize[size-1] = 4;
    float cross;
    float mut ;
    float accuracy;
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
    std::cout<<"\nEnter accuracy (Enter 0 if u want max gen): ";
    std::cin>>accuracy;

    
    std::cout<<"Start GA:\n";
    GA test(layerSize, pop,cross,mut,maxgen);
    test.setAccuracy(accuracy);
    test.CreateFullMaps();

        test.run();

    return 0 ;
    std::string filename = "BestChrom";

    
    test.SaveBestChrome(filename);
    std::cout<<"Press any key\n";
    char next;
    getchar();
    Game game(1,1,20,20);
    game.emptyMap();
    do
    {
        game.Drow();
        test.setIntput(game.getScan(0));
        test.ForwardFeed(0);
        
        std::vector<std::vector<float>> inp(1);
        inp[0]= test.getOutput();
        game.Input(inp);
        game.Logic();

    } while (game.getNumAlive()>0 && !_kbhit());
    std::cout<< game.getMaxStep();
    std::cout<<"Press any key\n";

    getchar();
    return 0;
}