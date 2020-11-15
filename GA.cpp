#include "GA.hpp"
#include <cmath>
#include <omp.h>
#include <cstdio>



GA::GA(std::vector<int> layerSize, int pop, float cross_chance, float mutate_chance, int max_generation){
    population.resize(pop);

    this->max_gen = max_generation;
    srand(clock());
   
    value.resize(layerSize.size());
    for (int i = 0; i < layerSize.size(); i++)
    {
        value[i].resize(layerSize[i]);
    }
    
    for(int i =0; i<pop; i++){
        population[i] = Chromosome(layerSize);
    }
    
    //std::clock_t start , finish;
    // map.resize(240);
    // std::cout<<"Start generate map\n";
    // start = clock();
    // unsigned int count =0;
    // for (int i = 0; i < map.size(); i++)
    // {
    //     map[i].gener(8);
    //     if(checkMap(map, i)){
    //         i--;
    //     }
    //     std::cout<<count++<<"\t"<<i<<std::endl;
    // }
    // finish = clock();
    //std::cout<<"Finish generate map. Total time "<<((double) finish - start)/((double) CLOCKS_PER_SEC) <<"\n";
    population[0].setChance_cross(cross_chance);
    population[0].setChanse_mutate(mutate_chance);
}


void GA::Crossover(int a , int b){
    newpop.push_back(this->population[a].Crossover(this->population[b]));
    
}

void GA::Mutation(int a){
    this->population[a].Mutation();
}

void GA::Fitness(int index){
    int i = 0;
    do
    {
        this->value[0] = FullMaps[i].getBordandFood();
        this->ForwardFeed(index);
        population[index].step++;
        int max_index =0;
        float max = value[value.size()-1][0];
        for (int k = 1; k < value[value.size()-1].size(); k++)
        {
            if(value[value.size()-1][k]>max){
                max = value[value.size()-1][k];
                max_index = k;
            }
        }
        
        if(max_index == 0){
            if(FullMaps[i].map[1]== -1){
                this->population[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[1]== 1){
                this->population[index].point++;
            }
        }
        if(max_index == 1){
            if(FullMaps[i].map[3]== -1){
               this->population[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[3]== 1){
                this->population[index].point++;
            }
        }
        if(max_index == 2){
            if(FullMaps[i].map[4]== -1){
                this->population[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[4]== 1){
                this->population[index].point++;
            }
        }
        if(max_index == 3){
            if(FullMaps[i].map[6]== -1){
                this->population[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[6]== 1){
                this->population[index].point++;
            }
        }

        
        
        i++;
    } while (i<FullMaps.size());
    
}


void GA::run(){
    std::cout << "Population " << population.size();
    std::cout << std::endl;
 //   std::cout << omp_get_num_threads()<< std::endl;
    std::cout.width(15);
    std::cout << "Generation";
    std::cout.width(15);
    std::cout << "MAX Step";
    std::cout.width(15); 
    std::cout<< "AVG";
    
    std::cout.width(15);
    std::cout << "Mutate coef";
    std::cout.width(15);
    std::cout << "Mutate chanse";
    std::cout.width(15);
    std::cout << "Cross chanse";
    std::cout.width(15);
    std::cout << "Time (sec)";
    std::cout.width(15);
    std::cout << "Podruad";
    
    std::cout << std::endl;
    clock_t start, end;
    int generation = 0;
    int count =0 ;
    do
    {
        start = clock();
        
//#pragma omp parallel for
        for (int iter =0 ; iter <  population.size(); iter++)
        {
            
            this->Fitness(iter);
        }
        
        

        this->SortStep();
        //this->SortPoint();
        newpop.resize(population.size());
        int index_pop = 0;
        do{
//#pragma omp parallel for
            for (int i = 0; i < int(population.size() * 0.1) + 1; i++)
            {
                for (int j = 0; j < int(population.size() * 0.1) + 1; j++)
                {
                    if (i == j) {
                        newpop[index_pop] = population[i];
                        newpop[index_pop].step = 0;
                        newpop[index_pop].point = 0;
                        index_pop++;
                        continue;
                    }
                    newpop[index_pop] = population[i].Crossover(population[j]);
                    newpop[index_pop].Mutation();
                    newpop[index_pop].step = 0;
                    newpop[index_pop].point = 0;
                    index_pop++;
                    if (index_pop >= population.size())
                        break;
                }
                if (index_pop >= population.size())
                    break;
            }

        }while (index_pop < population.size());


        this->max_step.push_back(maxStep());
        this->AVG.push_back(avgStep());

        if (generation > 3) {
            float dMax = 0;
            float dAVG = 0;
            dMax = 1.f * max_step[max_step.size() - 1] - 2.f * max_step[max_step.size() - 2] + 1.f * max_step[max_step.size() - 3];
            dAVG = 1.f * AVG[AVG.size() - 1] - 2.f * AVG[AVG.size() - 2] + 1.f * AVG[AVG.size() - 3];
            if (dMax == 0)
            {
                if(Chromosome::chance_mutate < 0.8f)
                    Chromosome::chance_mutate += 0.005f;
                if(dAVG<=0)
                    if (Chromosome::chance_cross < 0.6f) {
                        Chromosome::chance_cross += 0.005f;
                    }
                if (Chromosome::mutation_coef > 0.001f) {
                    Chromosome::mutation_coef -= 0.001f;
                }
            }
            else
            {
                if (Chromosome::mutation_coef< 0.8f) {
                    Chromosome::mutation_coef += 0.001f;
                }
            }



            if (Chromosome::mutation_coef > 0.001f && dAVG > 0)
                Chromosome::mutation_coef -= 0.001f;
            if (Chromosome::mutation_coef < 0.80f && dAVG <= 0)
                Chromosome::mutation_coef += 0.001f;

        }
        //softMaxStep();
        if(generation >2){
            if(max_step[max_step.size()-1]==max_step[max_step.size()-2]){
                count++;
            }else{
                count =0;
            }
        }
        
        std::cout.width(15);
        std::cout << generation;
        std::cout.width(15);
        std::cout <<this->max_step[max_step.size()-1];
        std::cout.width(15);
        std::cout << AVG[AVG.size()-1];
        std::cout.width(15);
        std::cout << population[population.size()-1].mutation_coef;
        std::cout.width(15);
        std::cout << population[population.size() - 1].chance_mutate;
        std::cout.width(15);
        std::cout << population[population.size() - 1].chance_cross;
        


        /*std::cout.width(15);
        std::cout << "Num chrom";
        std::cout.width(15);
        std::cout << "Matation coef";
        std::cout.width(15);
        std::cout << "Mutate chance";
        std::cout.width(15);
        std::cout << "Cross Chance";
        std::cout << std::endl;
        for (int i = 0; i < population.size(); i++)
        {
            std::cout.width(15);
            std::cout << i;
            std::cout.width(15);
            std::cout << population[i].mutation_coef;
            std::cout.width(15);
            std::cout << population[i].chance_mutate;
            std::cout.width(15);
            std::cout << population[i].chance_cross;
            std::cout << std::endl;
        }
        std::cout << "_______________________________________________________________";
        std::cout << std::endl;*/
        this->population = newpop;
        //std::cout << "Popul = " << population.size()<<std::endl;
        newpop.clear();
        generation++;
        end = clock();
        std::cout.width(15);
        std::cout << (end - start) / CLOCKS_PER_SEC;
        std::cout.width(15);
        std::cout << count;
        std::cout << std::endl;
        if(max_gen>generation && max_gen!=0){
            break;
        }
    } while (avgStep()<FullMaps.size()*0.95&& !_kbhit());
    std::cout<<"Trening complite!\n\n";

}

float GA::act(float x){
    return 2.f/(1.f+expf(-x))-1.f;
}

bool GA::checkMap(std::vector<Map>& tmp,int index){
    for (int i = 0; i < index; i++)
    {
        if(tmp[i] == tmp[index])
            return  true;
    }
    return false;
}

int GA::maxStep(){
    int max = this->population[0].step;
    for (int i = 1; i < this->population.size(); i++)
    {
        if(max<this->population[i].step){
            max = population[i].step;
        }
    }
    return max;    
}


float GA::avgStep(){
    float avg = float(this->population[0].step);
    for (int i = 1; i < this->population.size(); i++)
    {
        avg += float(this->population[i].step);
    }
    return avg/float(this->population.size());
}

void GA::SortStep(){
    Chromosome tmp;
    for (int i = 0; i < population.size(); i++)
    {
        for (int j = 1; j < population.size(); j++)
        {
            if(population[j-1].step<population[j].step){
                tmp = population[j-1];
                population[j-1] = population[j];
                population[j] = population[j-1];
            }
        }
    }
    
}

void GA::SortPoint(){
    Chromosome tmp;
    for (int i = 0; i < population.size()*0.1; i++)
    {
        for (int j = 1; j < population.size()*0.1; j++)
        {
            if(population[j-1].point<population[j].point){
                tmp = population[j-1];
                population[j-1] = population[j];
                population[j] = population[j-1];
            }
        }
    }
    

}


void GA::ForwardFeed(int index = 0){
        for (int i = 0; i < value.size()-1; i++)
        {

            for (int j = 0; j < value[i+1].size(); j++)
            {
                float arg = this->population[index].w0[i][j];
                for(int k= 0; k< value[i].size(); k++){
                    arg+=this->population[index].weights[i][j][k]*value[i][k];
                }
                this->value[i+1][j] = act(arg);
            }
            
        }
}

void GA::CreateFullMaps(){
    int size = pow(3,8);
    int count = 0;
    this->FullMaps.resize(size);
    for (int i = 0; i < FullMaps.size(); i++)
    {
        FullMaps[i].map.resize(8);
    }
    
    
    for (int i0 = -1; i0 < 2; i0++)
    {
        
        for (int i1 = -1; i1 < 2; i1++)
        {
            
            for (int i2 = -1; i2 < 2; i2++)
            {
                
                for (int i3 = -1; i3 < 2; i3++)
                {
                    
                    for (int i4 = -1; i4 < 2; i4++)
                    {
                        
                        for (int i5 = -1; i5 < 2; i5++)
                        {
                            
                            for (int i6 = -1; i6 < 2; i6++)
                            {
                                
                                for (int i7 = -1; i7 < 2; i7++)
                                {
                                    this->FullMaps[count].map[0] = i0;
                                    this->FullMaps[count].map[1] = i1;
                                    this->FullMaps[count].map[2] = i2;
                                    this->FullMaps[count].map[3] = i3;
                                    this->FullMaps[count].map[4] = i4;
                                    this->FullMaps[count].map[5] = i5;
                                    this->FullMaps[count].map[6] = i6;
                                    this->FullMaps[count].map[7] = i7;
                                    count++;
                                }
                            }
                        }
                    }
                }
            } 
        }    
    }
    
    for (int i = 0; i < FullMaps.size(); i++)
    {
        if(!FullMaps[i].Check()){
            FullMaps.erase(FullMaps.begin() + i);
            i--;
        }
    }

    
   
    std::cout<<count<<std::endl;
    std::cout<<FullMaps.size()<<std::endl;
    
}



//void GA::softMaxStep() {
//
//   
//    for (int index = 0; index < population.size(); index++)
//    {
//        float max = population[0].step;
//
//        for (int i = 1; i < population.size(); i++)
//        {
//            if (max < population[i].step) {
//                max = population[i].step;
//            }
//        }
//        float soft = 0;
//        
//        for (int i = 0; i < population.size(); i++)
//        {
//            soft += expf(population[i].step - max);
//        }
//        soft = expf(population[index].step - max) / soft;
//        if (soft < 0.8f && soft>0.2f) {
//            population[index].chance_cross = soft;
//            population[index].chance_mutate = 1.f - soft;
//        }
//        else
//        {
//            if (soft <= 0.2f) {
//                population[index].chance_cross = 0.2f;
//                population[index].chance_mutate = 0.8f;
//            }
//            if(soft>=0.8f)
//            {
//                population[index].chance_cross = 0.8f;
//                population[index].chance_mutate = 0.2f;
//            }
//        }
//        
//    
//        std::cout.width(15);
//        std::cout << index;
//        std::cout.width(15);
//        std::cout << soft;
//        std::cout<<std::endl;
//    }
//
//
//    
//
//}