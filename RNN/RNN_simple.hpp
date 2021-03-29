#pragma once
#include "Layer.hpp"
#include <cmath>
#include <iostream>
#include <random>
class RNN_simple{
public:
    RNN_simple();
    RNN_simple(int input_size, int output_size, std::vector<int> hidden_layer_size);
    void Forwardfeed();
    int softmax();
    void setInput(std::vector<double>& input);
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