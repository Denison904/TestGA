#pragma once
#include <vector>
#include <cmath>
class MemoryBlock{
public:
    MemoryBlock();
    MemoryBlock(int size);
    void addNeurons(std::vector<double> input);
    std::vector<double> act_tanh(std::vector<double> x);
    std::vector<double> getOutput(std::vector<double> x);
    std::vector<double> neurons;
    std::vector<std::vector<double>> weights;
};