#pragma once 
#include <vector>
#include "RNN_simple.hpp"
class Chromosome_RNN:public RNN_simple{
public:
    int step;
    int point;
    bool done;
    Chromosome_RNN();
    Chromosome_RNN(int input_size, int output_size, int hidden_layer_size);
    Chromosome_RNN Crossover(const Chromosome_RNN& other);
    void Mutation();
    static double chance_mutate ;
    static double chance_cross ; 
    static double mutation_coef ;


    // Chromosome_RNN(const Chromosome_RNN& copy);
};