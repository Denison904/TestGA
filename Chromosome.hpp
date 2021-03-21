#pragma once
#include <vector>

class Chromosome{
public:
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> w0;
    int step;
    int point;
    Chromosome() {};
    Chromosome(std::vector<int> layerSize);
    void Copy(Chromosome &newChrom,  Chromosome other);
    Chromosome Crossover(Chromosome& other);
    void Mutation();
    static double chance_mutate ;
    static double chance_cross ; 
    static double mutation_coef ;
    void setChanse_mutate(double x);
    void setChance_cross(double x) ;
};