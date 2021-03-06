#include "RNN_simple.hpp"



RNN_simple::RNN_simple(){}

RNN_simple::RNN_simple(int input_size, int output_size, std::vector<int> hidden_layer_size ){
    // std::cout<<"Constructor RNN_simple Start\n";
    


    this->Input = Layer(input_size, hidden_layer_size[0]);
    this->Output= Matrix(output_size, 1);
    this->hiddenLayer.resize(hidden_layer_size.size());

    this->hiddenLayer[hidden_layer_size.size()-1] = Layer(hidden_layer_size[hidden_layer_size.size()-1], output_size);
    for(int i =0; i<hidden_layer_size.size()-1; i++){
        this->hiddenLayer[i] = Layer(hidden_layer_size[i], hidden_layer_size[i+1]);
    }
    this->size = hidden_layer_size.size()+1;
    this->memory.resize(hidden_layer_size.size());
    for (int i = 0; i < hidden_layer_size.size()-1; i++)
    {
        this->memory[i] = Layer(hidden_layer_size[i], hidden_layer_size[i + 1]);
    }
    this->memory[hidden_layer_size.size() - 1] = Layer(hidden_layer_size[hidden_layer_size.size() - 1], output_size);
    // std::cout<<"Constructor RNN_simple Start\n";
}


void RNN_simple::Forwardfeed(){
    this->hiddenLayer[0].addInput(this->Input.getOutput());
    for (int i = 1; i < this->hiddenLayer.size(); i++)
    {

        this->hiddenLayer[i].addInput(this->hiddenLayer[i-1].getOutput());
    }
    this->Output = this->hiddenLayer[this->hiddenLayer.size()-1].getOutput();
    // std::cout<<"\nOutput complite\n";
    this->NextBlock();
}

int RNN_simple::softmax(){
    int out = 0;
    double max =0;
    double sum = 0;
    for (int i = 0; i < this->Output.size(); i++)
    {
        sum += exp(this->Output[i][0]);
    }

    sum = 1.0/sum;
    max = this->Output[0][0]*sum;
    for (int i = 1; i < this->Output.size(); i++)
    {
        double a = exp(this->Output[i][0]);
        if(a>a){
            max = a;
        }
    }
    return out;
    
}

void RNN_simple::setInput(std::vector<double>& input){
     
    this->Input.setInput(Matrix(input, 1));
}

void RNN_simple::NextBlock(){
    for (int i = 0; i < this->hiddenLayer.size(); i++)
    {
        this->hiddenLayer[i].setInput(memory[i].getOutput());
    }
    
}

int RNN_simple::getIndexClass(){
    int  out = 0;
    for (int i = 1; i < this->Output.size(); i++)
    {
        if(this->Output[out]<this->Output[i]){
            out = i;
        }
    }
    return out;
}

void RNN_simple::ZeroNeurons(){
    for (int i = 0; i < this->hiddenLayer.size(); i++)
    {
        for (size_t j = 0; j < this->hiddenLayer[i].neurons.size(); j++)
        {
            this->hiddenLayer[i].neurons[j][0] = 0;
        }
        
    }
    for (int i = 0; i < this->memory.size(); i++)
    {
        for (size_t j = 0; j < this->memory[i].neurons.size(); j++)
        {
            this->memory[i].neurons[j][0] = 0;
        }
        
    }
    
    
}