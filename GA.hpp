#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include "Chromosome.hpp"
#include "Map.hpp"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <string>
class  GA{
public:
    GA();
    GA(std::vector<int> layeSize, int pop, float cross_chance, float mutate_chance, int max_generation);
    void Crossover(int a,int b);
    void Mutation(int a);
    void Fitness(int index);
    void run();
    float act(float x);
    bool checkMap(std::vector<Map>& tmp, int  index);
    int maxStep();
    float avgStep();

    int maxPoint();
    float avgPoint();

    void SortStep();
    void SortPoint();
    void setIntput(std::vector<float> input);
    std::vector<float> getOutput();
    void ForwardFeed(int index);
    void CreateFullMaps();
    void SaveStatistic();
    void SaveBestChrome(std::string filename);
    void setAccuracy(float a);

    
    //void softMaxStep();
    ~GA(){};
private:
    std::vector<Map> FullMaps;
    std::vector<int> max_step;
    std::vector<float> AVG_step;
    std::vector<int> max_point;
    std::vector<float> AVG_point;
    float accuracy;
    int max_gen;
    std::vector<Chromosome> population;
    std::vector<Chromosome> newpop;
    std::vector<Map> map;
    std::vector<std::vector<float>> value;
};