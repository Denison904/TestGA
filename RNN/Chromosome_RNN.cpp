#include "Chromosome_RNN.hpp"


double Chromosome_RNN::chance_cross = 0.5;
double Chromosome_RNN::chance_mutate = 0.5;
double Chromosome_RNN::mutation_coef = 1;

Chromosome_RNN::Chromosome_RNN():RNN_simple(){

}

Chromosome_RNN::Chromosome_RNN(int input_size, int output_size, std::vector<int> hidden_layer_size):RNN_simple(input_size, output_size, hidden_layer_size){
    // std::cout<<"Constructor Chromosome_RNN Start\n";
    this->step = 0;
    this->point = 0;
    this->done = true;
    // std::cout<<"Constructor Chromosome_RNN END\n";
}

Chromosome_RNN Chromosome_RNN::Crossover(const Chromosome_RNN& other){
    Chromosome_RNN new_Chrom(other);
    for (int i = 0; i < this->Input.weights.size(); i++)
    {
        for (size_t j = 0; j < this->Input.weights[i].size(); j++)
        {
                if ((rand()%10000000)*0.0000001<this->chance_cross )
                {
                    if(rand()%2==1){
                        new_Chrom.Input.weights[i][j]=this->Input.weights[i][j];
                    }                    
                }
        }
    }
    for (int i = 0; i < this->Input.threshold.size(); i++)
    {
        if ((rand()%10000000)*0.0000001<this->chance_cross )
        {
            if(rand()%2==1){
                new_Chrom.Input.threshold[i]=this->Input.threshold[i];
            }                    
        }
    }
    for (size_t h = 0; h < this->hiddenLayer.size(); h++)
    {
        for (int i = 0; i < this->hiddenLayer[h].weights.size(); i++)
        {
            for (size_t j = 0; j < this->hiddenLayer[h].weights[i].size(); j++)
            {
                if ((rand()%10000000)*0.0000001<this->chance_mutate )
                {
                    if(rand()%2==1){
                        new_Chrom.hiddenLayer[h].weights[i][j]+=this->hiddenLayer[h].weights[i][j];
                    }
                }
            }
            
        }
        for (int i = 0; i < this->hiddenLayer[h].threshold.size(); i++)
        {
            if ((rand()%10000000)*0.0000001<this->chance_mutate )
            {
                if(rand()%2==1){
                    new_Chrom.hiddenLayer[h].threshold[i][0]+=this->hiddenLayer[h].threshold[i][0];
                }                
            }
        }
    }
    for (size_t m = 0; m < memory.size(); m++)
    {
        for (int i = 0; i < this->memory[m].weights.size(); i++)
        {
            for (size_t j = 0; j < this->memory[m].weights[i].size(); j++)
            {
                if ((rand()%10000000)*0.0000001<this->chance_mutate )
                {
                    if(rand()%2==1){
                        new_Chrom.memory[m].weights[i][j]+=this->memory[m].weights[i][j];
                    }
                }
            }
        }
    }
    return new_Chrom;
}

void Chromosome_RNN::Mutation(){
    for (int i = 0; i < this->Input.weights.size(); i++)
    {
        for (size_t j = 0; j < this->Input.weights[i].size(); j++)
        {
                if ((rand()%10000000)*0.0000001<this->chance_mutate )
                {
                    if(rand()%2==1){
                        this->Input.weights[i][j]+=this->mutation_coef;
                    }else{
                        this->Input.weights[i][j]-=this->mutation_coef;
                    }
                    
                }
        }
        
    }
    for (int i = 0; i < this->Input.threshold.size(); i++)
    {
        if ((rand()%10000000)*0.0000001<this->chance_mutate )
        {
            if(rand()%2==1){
                this->Input.threshold[i][0]+=this->mutation_coef;
            }else{
                this->Input.threshold[i][0]-=this->mutation_coef;
            }
            
        }
    }
    for (size_t h = 0; h < this->hiddenLayer.size(); h++)
    {
        for (int i = 0; i < this->hiddenLayer[h].weights.size(); i++)
        {
            for (size_t j = 0; j < this->hiddenLayer[h].weights[i].size(); j++)
            {
                if ((rand()%10000000)*0.0000001<this->chance_mutate )
                {
                    if(rand()%2==1){
                        this->hiddenLayer[h].weights[i][j]+=this->mutation_coef;
                    }else{
                        this->hiddenLayer[h].weights[i][j]-=this->mutation_coef;
                    }
                    
                }
            }
            
        }
        for (int i = 0; i < this->hiddenLayer[h].threshold.size(); i++)
        {
            if ((rand()%10000000)*0.0000001<this->chance_mutate )
            {
                if(rand()%2==1){
                    this->hiddenLayer[h].threshold[i][0]+=this->mutation_coef;
                }else{
                    this->hiddenLayer[h].threshold[i][0]-=this->mutation_coef;
                }
                
            }
        }
    }
    for (size_t m = 0; m < memory.size(); m++)
    {
        for (int i = 0; i < this->memory[m].weights.size(); i++)
        {
            for (size_t j = 0; j < this->memory[m].weights[i].size(); j++)
            {
                if ((rand()%10000000)*0.0000001<this->chance_mutate )
                {
                    if(rand()%2==1){
                        this->memory[m].weights[i][j]+=this->mutation_coef;
                    }else{
                        this->memory[m].weights[i][j]-=this->mutation_coef;
                    }
                    
                }
            }
        }
    }

}

// Chromosome_RNN::Chromosome_RNN(const Chromosome_RNN& copy){
//     this->step =0;
//     this->done = 0;
//     this->Input = copy.Input;
//     this->hiddenLayer=copy.hiddenLayer;
//     this->memory = copy.memory;
// }