#pragma once
#include <vector>

class Chromosome{
public:
    std::vector<std::vector<std::vector<float>>> weights;
    std::vector<std::vector<float>> w0;
    int step;
    int point;
    Chromosome() {};
    Chromosome(std::vector<int> layerSize);
    void Copy(Chromosome &newChrom,  Chromosome other);
    Chromosome Crossover(Chromosome& other);
    void Mutation();
    static float chance_mutate ;
    static float chance_cross ; 
    static float mutation_coef ;
    void setChanse_mutate(float x);
    void setChance_cross(float x) ;
};