#include "GA.hpp"
#include <cmath>
#include <omp.h>
#include <cstdio>
#define ONE_NEURON
#define TREATMENT
#define POINT
GA::GA(){
   
};

GA::GA(std::vector<int> layerSize, int pop, float cross_chance, float mutate_chance, int max_generation){
    this->accuracy = 0.9f;
    
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
        int max_index = 0;
        float max = value[value.size()-1][0];
        for (int k = 1; k < value[value.size()-1].size(); k++)
        {
            if(value[value.size()-1][k]>max){
                max = value[value.size()-1][k];
                max_index = k;
            }
        }
        
        if(max_index == 0){
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
        if(max_index == 1){
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
    std::cout<< "AVG Step";
    #ifdef POINT
    std::cout.width(15);
    std::cout << "MAX Point";
    std::cout.width(15); 
    std::cout<< "AVG Point";
    #endif
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
    clock_t total_start, total_end;
    int generation = 0;
    int count =0 ;
    std::string filename;
    time_t now = time(0);
    tm *currentTime=gmtime(&now);
    filename+= std::to_string(+currentTime->tm_year+1900);
    filename+="_";
    filename+= std::to_string(currentTime->tm_mon+1);
    filename+="_";
    filename+= std::to_string(currentTime->tm_mday);
    filename+="_";
    filename+=std::to_string(currentTime->tm_hour);
    filename+="_";
    filename+= std::to_string(currentTime->tm_min);
    filename+=".csv";
    char section = ';';
    filename = "Statistica_" + filename;
    std::ofstream statistic(filename);

    if(statistic.is_open()){
        statistic<<"Population"<<section<<this->population.size()<<"\n";
        statistic<<"Max generation"<<section<<this->max_gen<<"\n";
        statistic<<"Point"<<section;
        #ifdef POINT
        statistic<<"True\n";
        #endif
        #ifndef POINT
        statistic<<"False\n";
        #endif
        statistic<<"Hidden layer"<<section<<value.size()-2<<"\n";
        for (int i = 1; i < value.size()-1; i++)
        {
            statistic<<"Hidden layer #"<<i<<section<<value[i].size()<<"\n";
        }
        
        statistic<< "Generation"<<section;
        statistic<< "MAX Step"<<section;
        statistic<< "AVG Step"<<section;
        #ifdef POINT
            statistic<<"MAX Point"<<section<<"AVG Point"<<section;
        #endif
        statistic<< "Mutate coef"<<section;
        statistic<< "Mutate chanse"<<section;
        statistic<< "Cross chanse"<<section;
        statistic<< "Time (sec)"<<section;
        statistic<< "Consecutiv"<<section;
        statistic<<"\n";
    }else{
        std::cout<<"ERROR FILE IS NOT OPEN!\n";
    }
    total_start = clock();
    do
    {
        start = clock();
        
//#pragma omp parallel for
        for (int iter =0 ; iter <  population.size(); iter++)
        {
            
            this->Fitness(iter);
        }
        
        

        this->SortStep();
        #ifdef POINT
        this->SortPoint();
        #endif
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
        this->AVG_step.push_back(avgStep());
        #ifdef POINT
        this->max_point.push_back(population[0].point);
        this->AVG_point.push_back(avgPoint());
        #endif
        if (generation > 3) {
            float dMax = 0;
            float dAVG = 0;
            dMax = 1.f * max_step[max_step.size() - 1] - 2.f * max_step[max_step.size() - 2] + 1.f * max_step[max_step.size() - 3];
            dAVG = 1.f * AVG_step[AVG_step.size() - 1] - 2.f * AVG_step[AVG_step.size() - 2] + 1.f * AVG_step[AVG_step.size() - 3];
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
        std::cout <<population[0].step;
        std::cout.width(15);
        std::cout << AVG_step[AVG_step.size()-1];
        #ifdef POINT
        std::cout.width(15);
        std::cout << max_point[max_point.size()-1];
        std::cout.width(15); 
        std::cout<< AVG_point[AVG_point.size()-1];
        #endif
        std::cout.width(15);
        std::cout << population[population.size()-1].mutation_coef;
        std::cout.width(15);
        std::cout << population[population.size() - 1].chance_mutate;
        std::cout.width(15);
        std::cout << population[population.size() - 1].chance_cross;
        



        this->population = newpop;

        newpop.clear();

        end = clock();
        std::cout.width(15);
        std::cout << (end - start) / CLOCKS_PER_SEC;
        std::cout.width(15);
        std::cout << count;
        std::cout << std::endl;


        if(statistic.is_open()){
            statistic<<generation<<section<<max_step[max_step.size()-1]<<section<<AVG_step[AVG_step.size()-1]<<section;
            #ifdef POINT
            statistic<<max_point[max_point.size()-1]<<section<<AVG_point[AVG_point.size()-1]<<section;
            #endif
            statistic<<Chromosome::mutation_coef<<section<<Chromosome::chance_mutate<<section<<Chromosome::chance_cross<<section<<(end - start) / CLOCKS_PER_SEC<<section<<count<<"\n";
        }



        generation++;
        if(max_gen==generation && max_gen!=0){
            std::cout<<"Achieve Max generation!\n";
            break;
        }
     
        if(AVG_step[AVG_step.size()-1]>FullMaps.size()*accuracy && accuracy!=0){
            std::cout<<"Accuracy achieved!\n";
            break;
        }

    } while (!_kbhit());
    total_end = clock();
    std::cout<<"Trening complite!\n\n";
    statistic << "\nTotal time (Sec)"<<section << (total_end - total_start)/CLOCKS_PER_SEC;
    statistic.close();
    
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

float GA::avgPoint(){
    float avg = float(this->population[0].point);
    for (int i = 1; i < this->population.size(); i++)
    {
        avg += float(this->population[i].point);
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
    int max = population[0].step;
    for (int i = 1; population[i].step == max; i++)
    {
        for (int j = 1; population[j].step==max; j++)
        {
            tmp = population[j-1];
            population[j-1] = population[j];
            population[j] = population[j-1];
        }
    }
    


}

void GA::setIntput(std::vector<float> input){
    if(this->value[0].size()== input.size())
        value[0] = input;
    else
    {
        std::cout<<"Error input vector size!\n";
        exit(1);
    }

}


std::vector<float> GA::getOutput(){
    std::vector<float> tmp(value[value.size()-1].size());
    float max = value[value.size()-1][0];
    for (int i = 1; i < value[value.size()-1].size(); i++)
    {
        if(value[value.size()-1][i]>max){
            max = value[value.size()-1][i];
        }
    }
    float soft=0;
    for (int i = 0; i < value[value.size()-1].size(); i++)
    {
        soft+=expf(value[value.size()-1][i]-max);
    }

    for (int i = 0; i < value[value.size()-1].size(); i++)
    {
        tmp[i] = expf( value[value.size()-1][i]-max)/soft; 
    }
    


    
    return tmp;
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
    std::cout<<FullMaps.size()*accuracy<<std::endl;
}



void GA::SaveBestChrome(std::string filename){
    time_t now = time(0);
    
    // char* dt = ctime(&now);
    // filename+=dt;
    tm *currentTime=gmtime(&now);
    filename+="_";
    filename+= std::to_string(+currentTime->tm_year+1900);
    filename+="_";
    filename+= std::to_string(currentTime->tm_mon+1);
    filename+="_";
    filename+= std::to_string(currentTime->tm_mday);
    filename+="_";
    filename+=std::to_string(currentTime->tm_hour);
    filename+="_";
    filename+= std::to_string(currentTime->tm_min); 
    filename+=".txt";
    std::ofstream file(filename);
    if(file.is_open()){
        file<<value.size()<<"\n";
        for (int i = 0; i < value.size(); i++)
        {
            file<<value[i].size()<<" ";
        }
        for (int i = 0; i < population[0].weights.size(); i++)
        {
            for (int j = 0; j < population[0].weights[i].size(); j++)
            {
                for (int k = 0; k < population[0].weights[i][j].size(); k++)
                {
                    file<<population[0].weights[i][j][k]<<" ";
                }
                file <<"\n";
            }
            file<<"\n";
        }
        file<<"\n";
        for (int i = 0; i < population[0].w0.size(); i++)
        {
            for (int j = 0; j < population[0].w0[i].size(); j++)
            {
                file<<population[0].w0[i][j]<<" ";
            }
            file<<"\n";
        }
        file.close();
        
        
        
    }else{
        std::cout<<"File isn't open!\n";
        return;
    }


}


void GA::setAccuracy(float a){
    this->accuracy = a;
}