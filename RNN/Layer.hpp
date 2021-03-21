#pragma once
#include "Matrix.hpp"
#include <vector>
#include <iostream>
class Layer{
public:
    Layer();
    Layer(int input, int output);
    void setInput(Matrix neurons);
    void addInput(Matrix neurons);
    
    Matrix getOutput();
    Matrix act_tanh(Matrix x);
    
    double getRandom();

    Matrix neurons;
    Matrix weights;
    Matrix threshold;
};