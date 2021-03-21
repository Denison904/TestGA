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
    GA(std::vector<int> layeSize, int pop, double cross_chance, double mutate_chance, int max_generation);
    void Crossover(int a,int b);
    void Mutation(int a);
    void Fitness(int index);
    void run();
    double act(double x);
    bool checkMap(std::vector<Map>& tmp, int  index);
    int maxStep();
    double avgStep();
    
    int maxPoint();
    double avgPoint();

    void SortStep();
    void SortPoint();
    void setIntput(std::vector<double> input);
    std::vector<double> getOutput();
    void ForwardFeed(int index);
    void CreateFullMaps();
    void SaveStatistic();
    void SaveBestChrome(std::string filename);
    void setAccuracy(double a);


    void newPop();
    
    //void softMaxStep();
    ~GA(){};
private:
    std::vector<Map> FullMaps;
    std::vector<int> max_step;
    std::vector<double> AVG_step;
    std::vector<int> max_point;
    std::vector<double> AVG_point;
    double accuracy;
    int max_gen;
    std::vector<Chromosome> population;
    std::vector<Chromosome> newpop;
    std::vector<Map> map;
    std::vector<std::vector<double>> value;
    std::vector<int> layerSize;
};