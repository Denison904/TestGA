#include "Layer.hpp"

Layer::Layer(){};

Layer::Layer(int input, int output){
    // std::cout<<"Constructor Layer Start\n";
 

    
    this->neurons= Matrix(input, 1);

    std::vector<std::vector<double>> w;
    w.resize(output);
    for (int i = 0; i <w.size(); i++)
    {
        w[i].resize(input);
        for (int j = 0; j <w[i].size(); j++)
        {
            w[i][j] = this->getRandom();
        }
        
    }
    this->weights = Matrix(w);
    std::vector<double> t(output);
    for (int i = 0; i < output; i++)
    {
       t[i] = this->getRandom();
    }
    this->threshold = Matrix(t, 1);
    // std::cout<<"Constructor Layer END\n";
    
}
void Layer::setInput(Matrix neurons){
    if(neurons.size()==this->neurons.size()&& neurons[0].size()==this->neurons[0].size())
        this->neurons = neurons;
}

void Layer::addInput(Matrix neurons){
    if(neurons.size()==this->neurons.size() && neurons[0].size()==this->neurons[0].size())
        this->neurons+=neurons;
    
}

Matrix Layer::getOutput(){
    Matrix answ;
    
    answ = this->weights*this->neurons-this->threshold;
    return this->act_tanh(answ);
}


Matrix Layer::act_tanh(Matrix x){
    for (size_t i = 0; i < x.size(); i++)
    {
        for (size_t j = 0; j < x[i].size();j++)
        {
            x[i][j]=(exp(x[i][j])-exp(-x[i][j]))/(exp(x[i][j])+exp(-x[i][j]));
        }
        
    }
    return x;
}
    


double Layer::getRandom(){
    return (rand()%int(1e6))*1e-6;
}