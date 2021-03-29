#pragma once 
#include "Chromosome_RNN.hpp"
#include "../Map.hpp"
#include "../MathModel/Header/Game.hpp"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <string>
#include <cmath>
#include <omp.h>
#include <cstdio>
#include <random>

class GA_RNN{
public:
    GA_RNN(int population, int input, int output, std::vector<int> numhidden);

    void start_learning();
    void sort();
    

    void Fitness(int index);
    void Print();
    void writeStats();
    void CreateFullMaps();
    int getMaxStep();
    void preprocessing_learning();
    void preprocessing_fitness(int index);
    void sortStep();
    void set_max_generation_preprocessing(int max);
    void set_max_generation(int max);

    RNN_simple get_rnn();
    
private:
    std::vector<Map> FullMaps;
    std::vector<Chromosome_RNN> chromos;
    int min=0;
    int generation=0;
    int numofdone = 0;
    std::fstream stats;
    std::vector<std::vector<int>> coord;    
    int max_generation_preprocessing;
    int max_generation;

};