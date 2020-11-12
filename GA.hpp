#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include "Chromosome.hpp"
#include "Map.hpp"
#include <iostream>
#include <ctime>
class  GA{
public:
    GA(){};
    GA(int pop, float cross_chance, float mutate_chance, int max_generation);
    void Crossover(int a,int b);
    void Mutation(int a);
    void Fitness(int index);
    void run();
    float act(float x);
    bool checkMap(Map& tmp, int  index);
    int maxStep();
    float avgStep();
    void SortStep();
    void SortPoint();
    //void softMaxStep();
    ~GA(){};
private:
    std::vector<int> max_step;
    std::vector<float> AVG;
    float cross_chance;
    float mutate_chance;
    int max_gen;
    std::vector<Chromosome> population;
    std::vector<Chromosome> newpop;
    std::vector<Map> map;
    std::vector<std::vector<float>> value;
};