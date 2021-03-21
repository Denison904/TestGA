#include "Chromosome.hpp"
#include <iostream>
Chromosome::Chromosome(std::vector<int> layerSize){
    weights.resize(layerSize.size()-1);
    
    for (int i = 0; i < weights.size(); i++) {
        weights[i].resize(layerSize[i + 1]); 
        for (int j = 0; j < weights[i].size(); j++)
        {
            weights[i][j].resize(layerSize[i]);
            for (int k = 0; k < weights[i][j].size(); k++)
            {
                weights[i][j][k] = (rand() % 50000) * 0.0001f - 2.5f;
            }
        }
    }

    w0.resize(layerSize.size()-1);
    for (int i = 0; i < w0.size(); i++)
    {
        w0[i].resize(layerSize[i+1]);
        for(int j = 0; j < w0[i].size(); j++)
        {
            w0[i][j] =rand()%5000*0.001f - 2.5f; 
        }
    }
    this->step = 0;
    this->point = 0;

}


double Chromosome::chance_mutate = 0.5f;
double Chromosome::chance_cross = 0.5f;
double Chromosome::mutation_coef = 1.f;


void Chromosome::Copy(Chromosome& newChrom, Chromosome other){
    newChrom.step = 0;
    newChrom.weights= other.weights;
    newChrom.w0 = other.w0;
}


Chromosome Chromosome::Crossover(Chromosome& other){
    Chromosome newChrom;
    this->Copy(newChrom, *this);
    for(int  i =0; i<this->weights.size();i++){
        for (int j = 0; j < this->weights[i].size(); j++)
        {
            for (int k = 0; k < this->weights[i][j].size(); k++)
            {
                if ((rand()%100000)*0.00001<other.chance_cross )
                {
                    newChrom.weights[i][j][k]=other.weights[i][j][k];
                }
                
            }
        }
    }
    for (int i = 0; i < this->w0.size(); i++)
    {
        for(int j =0; j<this->w0[i].size(); j++)
        {
            if ((rand()%100000)*0.00001<other.chance_cross )
            {
                newChrom.w0[i][j]=other.w0[i][j];
            }
        }
    }
    
    return newChrom;
}

void Chromosome::Mutation(){
    for(int  i =0; i<this->weights.size();i++)
    {
        for (int j = 0; j < this->weights[i].size(); j++)
        {
            for (int k = 0; k < this->weights[i][j].size(); k++)
            {
                if ((rand()%100000)*0.00001f<this->chance_mutate )
                {
                    if(rand()%2==1){
                        this->weights[i][j][k]+=1.0f;
                    }else{
                        this->weights[i][j][k]-=this->mutation_coef;
                    }
                    
                }
                
            }
        }
    }
    for (int i = 0; i < this->w0.size(); i++)
    {
        for(int j =0; j<this->w0[i].size(); j++)
        {
            if ((rand()%100000)*0.00001f<this->chance_mutate )
            {
                if(rand()%2==1){
                        this->w0[i][j]+=1.0f;
                }
                else {
                    this->w0[i][j] -= 1.0f;
                }
            }
        }
    }
}




void Chromosome::setChanse_mutate(double x){
    this->chance_mutate = x;
}
void Chromosome::setChance_cross(double x){
    this->chance_cross = x;
}