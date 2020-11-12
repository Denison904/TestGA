#include "GA.hpp"

int main(){  


    int pop = 10000;
    float cross = 0.4f;
    float mut = 0.4f;
    int maxgen = 1000;
    std::cout<<"Start GA:\n";
    GA test(pop,cross,mut,maxgen);
    test.run();

    char tmp;
    std::cout << "Press any key\n";
    std::cin>>tmp;
    return 0;
}