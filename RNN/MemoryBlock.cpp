#include "MemoryBlock.hpp"

MemoryBlock::MemoryBlock(){}

MemoryBlock::MemoryBlock(int size){
    this->neurons.resize(size);
    this->weights.resize(size);
    for (size_t i = 0; i < size; i++)
    {
        this->weights[i].resize(size);
        for (size_t j = 0; j < size; j++)
        {
            this->weights[i][j] = rand()%int(1e6)*(1e-6);
        }
        
    }
    
}

void MemoryBlock::addNeurons(std::vector<double> input){
    this->neurons = input;
}

std::vector<double> MemoryBlock::getOutput(std::vector<double> input){
    this->neurons =input;
    std::vector<double> answ(input.size());

    return this->act_tanh(answ);
    
}

std::vector<double> MemoryBlock::act_tanh(std::vector<double> x){
    
    for (int i = 0; i < x.size(); i++)
    {
        x[i] =(exp(x[i])-exp(-x[i]))/(exp(x[i])+exp(-x[i]));
    }
    return x;
}