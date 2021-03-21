#pragma once
#include "Layer.hpp"
#include "MemoryBlock.hpp"
#include <cmath>
#include <iostream>

class RNN_simple{
public:
    RNN_simple();
    RNN_simple(int input_size, int output_size, int hidden_layer_size);
    void Forwardfeed();
    int softmax();
    void setInput(std::vector<double> input);
    void NextBlock();
    int getIndexClass();
    void ZeroNeurons();
protected:
    int size;
    Layer Input;
    std::vector<Layer> hiddenLayer;
    Matrix Output;
    std::vector<Layer> memory;
};