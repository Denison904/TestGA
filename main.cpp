#define BREAK

#include "GA.hpp"
#include <string>
#include <iostream>
#include <ctime>
#include "MathModel\Header\Game.hpp"
#include "RNN\GA_RNN.hpp"


int main(){ 
    // RNN_simple rnn(4,2,2);
    // std::vector<double> input(4);
    // while(true){
    //     for (size_t i = 0; i < 4; i++)
    //     {
    //         input[i] = (rand()%int(1e5))*1e-5;
    //     }

    //     rnn.setInput(input);
    //     rnn.Forwardfeed();
    //     std::cout<<rnn.getIndexClass()<<std::endl;
        
    // }
    int pop = 5000;
    int max_pre, max, num_of_hidden;
    std::cout<<"Enter pop, max_pre, max , num of hidden layer\n";
    std::cin>>pop>>max_pre>>max>>num_of_hidden;
    std::vector<int> hl(num_of_hidden);
    for (size_t i = 0; i < num_of_hidden; i++)
    {

        std::cout<<"Enter hl["<<i<<"]: ";
        std::cin>>hl[i];
    }
    std::cout<<"Do u need preprocessing?\n";
    char preproc;
    std::cin>>preproc;

    GA_RNN rnn_ga(pop, 8, 4, hl);
    if(preproc=='y')
    {
        rnn_ga.set_max_generation_preprocessing(max_pre);
        rnn_ga.preprocessing_learning();
    }   
    rnn_ga.set_max_generation(max);

    rnn_ga.start_learning();
    RNN_simple rnn = rnn_ga.get_rnn();
    std::cout<<"Press any kay\n";
    char a; 
    std::cin>>a;
    Game game(1, 1, 15, 15);
    do
    {
        game.Drow();
        rnn.setInput(game.getScan(0));
        rnn.Forwardfeed();
        std::vector<int> tmp={rnn.getIndexClass()};
        game.Input(tmp);

        game.Logic();
    } while (game.getNumAlive()>0);
    std::cout<<"Step: "<<game.getStep(0)<<std::endl;
    std::cout<<"Press any kay\n";
   
    std::cin>>a;
    return 0;



    //int size;
    //std::vector<int> layerSize;
    //std::cout<<"Enter the number of hidden layer: ";
    //std::cin>>size;
    //size+=2;
    //layerSize.resize(size);
    //layerSize[0] = 8;//WARNING!
    //for (int i = 1; i < size-1; i++)
    //{
    //    std::cout<<"\nEnter size layer number "<<i<<": ";
    //    std::cin>>layerSize[i];
    //}
    //layerSize[size-1] = 4;
    //double cross;
    //double mut ;
    //double accuracy;
    //int maxgen ;
    //int pop;
    //std::cout<<"\nEnter population: ";
    //std::cin>>pop;
    //std::cout<<"\nEnter crossover chance(0,1): ";
    //std::cin>>cross;
    //std::cout<<"\nEnter nutation chance (0,1): ";
    //std::cin>>mut;
    //std::cout<<"\nEnter max generation (Enter 0 if you want max gen): ";
    //std::cin>>maxgen;
    //std::cout<<"\nEnter accuracy (Enter 0 if u want max gen): ";
    //std::cin>>accuracy;

    //
    //std::cout<<"Start GA:\n";
    //GA test(layerSize, pop,cross,mut,maxgen);
    //test.setAccuracy(accuracy);
    //test.CreateFullMaps();

    //test.run();


    //std::string filename = "BestChrom";

    //
    //test.SaveBestChrome(filename);
    //std::cout<<"Press any key\n";
    //char next;
    //getchar();
    //Game game(1,1,20,20);

    //std::cout<<"Start DO\n";
    //game.emptyMap();
    //
    //do
    //{
    //    game.Drow();
    //    test.setIntput(game.getScan(0));
    //    test.ForwardFeed(0);
    //    
    //    std::vector<std::vector<double>> inp(1);
    //    inp[0]= test.getOutput();
    //    game.Input(inp);
    //    game.Logic();
    //    
    //} while (game.getNumAlive()>0 && !_kbhit());
    //std::cout<< game.getMaxStep();
    //std::cout<<"Press any key\n";
    //getchar();
    //game = Game(1,1,20,20);
    //game.setMode(game.Mode::Stat);
    //game.setNumofBorderRand(10);
    //do
    //{
    //    game.Drow();
    //    test.setIntput(game.getScan(0));
    //    test.ForwardFeed(0);
    //    
    //    std::vector<std::vector<double>> inp(1);
    //    inp[0]= test.getOutput();
    //    game.Input(inp);
    //    game.Logic();
    //    
    //} while (game.getNumAlive()>0 && !_kbhit());
    //std::cout<< game.getMaxStep();
    //std::cout<<"Press any key\n";
    //getchar();
    //return 0;
}