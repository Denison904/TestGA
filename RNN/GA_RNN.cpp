#include "GA_RNN.hpp"

GA_RNN::GA_RNN(int population, int input, int output,int numhidden=1 ){
    // std::cout<<"Constructor GA_RNN Start\n";
    this->chromos.resize(population);
    for (size_t i = 0; i < population; i++)
    {
        // std::cout<<"Constructor RNN "<<i<<"\n";
        this->chromos[i] = Chromosome_RNN(input, output,numhidden);
    }
    // std::cout<<"Constructor GA_RNN END\n";
}

void GA_RNN::start_learning(){
    
    std::cout<<"Preprocessing\n";
    
    this->preprocessing_learning();
    std::string filename = "RNN_stats";
    time_t now = time(0);
    std::cout<<filename;
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
    filename+=".csv";
    std::ofstream file(filename);
    this->coord.resize(1);
    this->coord[0].resize(2);
    std::cout<<"START\n";
    std::cout.width(15);
    std::cout << "Generation";
    std::cout.width(15);
    std::cout << "MIN Step";
    std::cout.width(15);
    std::cout << "MAX Step";
    std::cout.width(15);
    std::cout << "Count done";
    std::cout.width(15);
    std::cout << "Time (sec)";

    clock_t start, end;
    clock_t total_start, total_end;
    total_start = clock();
    Chromosome_RNN::mutation_coef = 1.0;
    do
    {
        std::cout<<"\n";
        start = clock();
        this->coord[0][0] = rand()%13+1;
        this->coord[0][1] = rand()%13+1;
        for (size_t i = 0; i < chromos.size(); i++)
        {
            // std::cout<<"Fitness "<<i<<std::endl;
            this->Fitness(i);
        }
        
        int max_step = this->getMaxStep();
        for (size_t i = 0; i < chromos.size(); i++)
        {
            this->chromos[i].ZeroNeurons();
        }
        
        this->sort();
        std::vector<Chromosome_RNN>  newChrom(chromos.size());
        int index_pop = 0;
        do {
            //#pragma omp parallel for
            for (int i = 0; i < int(chromos.size() * 0.25) + 1; i++)
            {
                for (int j = 0; j < int(chromos.size() * 0.25) + 1; j++)
                {
                    if (i == j) {
                        newChrom[index_pop] = chromos[i];
                        newChrom[index_pop].step = 0;
                        newChrom[index_pop].point = 0;
                        index_pop++;
                        continue;
                    }
                    newChrom[index_pop] = chromos[i].Crossover(chromos[j]);
                    newChrom[index_pop].Mutation();
                    newChrom[index_pop].step = 0;
                    newChrom[index_pop].point = 0;
                    index_pop++;
                    if (index_pop >= chromos.size())
                        break;
                }
                if (index_pop >= chromos.size())
                    break;
            }

        } while (index_pop < chromos.size());

        this->chromos = newChrom;
        newChrom.clear();
        end = clock();
        int count_done =0;
        for (int i = 0; i < this->chromos.size(); i++)
        {
            if(this->chromos[i].done)
                count_done++;
        }
        std::cout.width(15);
        std::cout << this->generation;
        std::cout.width(15);
        std::cout <<this->chromos[0].step;
        std::cout.width(15);
        std::cout <<max_step;
        std::cout.width(15);
        std::cout <<count_done;
        std::cout.width(15);
        std::cout <<(end-start)/CLOCKS_PER_SEC;
        //this->Print();
        //this->writeStats();
        if(this->generation>10)
            Chromosome_RNN::mutation_coef -=pow(1.5,(1-this->generation));
        this->generation++;

    } while (this->generation<9999999999);
    total_end = clock();
    std::cout<<"Trening complite!\n\n";
    std::cout << "\nTotal time (Sec) "<< (total_end - total_start)/CLOCKS_PER_SEC;
}

void GA_RNN::sort(){
    int last_done =-1;
    for (int i = 0; i < this->chromos.size(); i++)
    {
        for (int j = 0; j < this->chromos.size()-1; j++)
        {
            if (this->chromos[j].done==false&&this->chromos[j+1].done==true)
            {
                Chromosome_RNN tmp = this->chromos[j+1];
                this->chromos[j+1] = this->chromos[j]; 
                this->chromos[j] = tmp;
            }
            
        }
        
    }

    for (int i = 0; i < this->chromos.size(); i++)
    {
        if(chromos[i].done==false){
            last_done = i-1;
            break;
        }
    }

    if(last_done>=0)
    for (int i = 0; i <= last_done; i++)
    {
        for (int j = 0; j <= last_done-1; j++)
        {
            if (this->chromos[j].step>this->chromos[j+1].step)
            {
                Chromosome_RNN tmp = this->chromos[j+1];
                this->chromos[j+1] = this->chromos[j]; 
                this->chromos[j] = tmp;
            }
        }
        
    }

    for (int i = last_done+1; i < this->chromos.size(); i++)
    {
        for (int j = last_done+1; j < this->chromos.size()-1; j++)
        {
            if (this->chromos[j].step<this->chromos[j+1].step)
            {
                Chromosome_RNN tmp = this->chromos[j + 1];
                this->chromos[j + 1] = this->chromos[j];
                this->chromos[j] = tmp;
            }
        }
    }
    
    
    
}


void GA_RNN::Fitness(int index){
    // std::cout<<"\nCreate game\n";
    Game game(1,1,15,15);// добавить в коструктор или отдельные фунции для параметров
    // std::cout<<"\nCreate coord food\n";
    if(this->coord[0][1]==15/2)
        coord[0][1]++;
    // std::cout<<"\nSet coord\n";
    game.setFood(coord);
    std::vector<int> inp(1);
    int numerate = 0;
    this->chromos[index].ZeroNeurons();
    while (game.getNumAlive()>0&& game.getPoint(0)==0)
    {
        std::vector<double> vec = game.getScan(0);
        std::vector<double> tmp(vec.size());
        for (int i = 0; i < vec.size(); i++)
        {
            tmp[i] = double(vec[i]);
        } 
        // std::cout<<"\nSet input\n";
        this->chromos[index].setInput(tmp);
        // std::cout<<"\nStart forwardfeed\n";
        this->chromos[index].Forwardfeed();
        // std::cout<<"\nComplite Forwardfeed\n";
        inp[0]=this->chromos[index].getIndexClass();
        // game.Drow();
        game.Input(inp);
        // std::cout<<"\nStart logic\n";
        game.Logic();
        // std::cout<<game.getNumAlive()<<"\n";
        // std::cout<<"Numerate "<< numerate++<<"\n";
    }
    this->chromos[index].step = game.getStep(0);
    if(game.getPoint(0)>0)
        this->chromos[index].done = true;
    else
        this->chromos[index].done = false;
    
 
    
}

void GA_RNN::Print(){

}

int GA_RNN::getMaxStep(){
    int max = 0;
    for (size_t i = 0; i < this->chromos.size(); i++)
    {
        if(this->chromos[i].step > max )
            max = this->chromos[i].step;
    }
    return max;
}


void GA_RNN::CreateFullMaps(){
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

}

void GA_RNN::preprocessing_learning(){
    Chromosome_RNN::mutation_coef = 1.0;
    this->CreateFullMaps();
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
   
    std::cout << std::endl;
    clock_t start, end;
    clock_t total_start, total_end;
    int generation = 0;
    int count =0 ;
    
    total_start = clock();
    do
    {
        start = clock();
        double AVG_step = 0;
        for (int iter =0 ; iter <  chromos.size(); iter++)
        {
            
            this->preprocessing_fitness(iter);
            AVG_step += this->chromos[iter].step;
        }
        AVG_step/=chromos.size();
        Chromosome_RNN tmp;
        
        for (int i = 0; i < chromos.size(); i++)
        {
            for (int j = 1; j < chromos.size(); j++)
            {
                if(chromos[j-1].step<chromos[j].step){
                    tmp = chromos[j-1];
                    chromos[j-1] = chromos[j];
                    chromos[j] = tmp;
                }
            }
        }        
        
        for (int i = 0; i < chromos.size(); i++)
        {
            for (int j = 1; j < chromos.size(); j++)
            {
                if(this->chromos[0].step ==this->chromos[j].step && this->chromos[0].step ==this->chromos[j-1].step)
                    if(chromos[j-1].point<chromos[j].point){
                        tmp = chromos[j-1];
                        chromos[j-1] = chromos[j];
                        chromos[j] = tmp;
                    }
            }
        }    

        

        
        std::vector<Chromosome_RNN>  newpop(chromos.size());
        int index_pop = 0;
        do{
//#pragma omp parallel for
            for (int i = 0; i < int(chromos.size() * 0.25) + 1; i++)
            {
                for (int j = 0; j < int(chromos.size() * 0.25) + 1; j++)
                {
                    if (i == j) {
                        newpop[index_pop] = chromos[i];
                        newpop[index_pop].step = 0;
                        newpop[index_pop].point = 0;
                        index_pop++;
                        continue;
                    }
                    newpop[index_pop] = chromos[i].Crossover(chromos[j]);
                    newpop[index_pop].Mutation();
                    newpop[index_pop].step = 0;
                    newpop[index_pop].point = 0;
                    index_pop++;
                    if (index_pop >= chromos.size())
                        break;
                }
                if (index_pop >= chromos.size())
                    break;
            }

        }while (index_pop < chromos.size());

        
       
        #ifdef POINT
        
        this->max_point.push_back(this->maxPoint());
        this->AVG_point.push_back(avgPoint());
        #endif
               //softMaxStep();
  
        
        std::cout.width(15);
        std::cout << generation;
        std::cout.width(15);
        std::cout <<chromos[0].step;
        std::cout.width(15);
        std::cout << AVG_step;
        #ifdef POINT
        std::cout.width(15);
        std::cout << max_point[max_point.size()-1];
        std::cout.width(15); 
        std::cout<< AVG_point[AVG_point.size()-1];
        #endif
        
        



        this->chromos = newpop;

        newpop.clear();

        end = clock();
        std::cout.width(15);
        std::cout << (end - start) / CLOCKS_PER_SEC;

        std::cout << std::endl;


       for (size_t i = 0; i < this->chromos.size(); i++)
       {
           this->chromos[i].ZeroNeurons();
       }
       

        if(this->generation>10)
            Chromosome_RNN::mutation_coef -=pow(1.5,(1-this->generation));

        generation++;

        if(AVG_step/this->FullMaps.size() > 0.99 || generation>25)
            break;
        

    } while (!_kbhit());
}

void GA_RNN::preprocessing_fitness(int index){
    // std::cout<<"Index "<<index<<std::endl;
    int i = 0;
    do
    {
        // std::cout<<"i "<<i<<std::endl;
        this->chromos[index].ZeroNeurons();
        this->chromos[index].setInput(FullMaps[i].getBordandFood());
        
        this->chromos[index].Forwardfeed();
        this->chromos[index].step++;
        int max_index = chromos[index].getIndexClass();
        
        if(max_index == 0){
            if(FullMaps[i].map[3]== -1){
                this->chromos[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[3]== 1){
                this->chromos[index].point++;
            }
        }
        if(max_index == 1){
            if(FullMaps[i].map[1]== -1){
               this->chromos[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[1]== 1){
                this->chromos[index].point++;
            }
        }
        if(max_index == 2){
            if(FullMaps[i].map[4]== -1){
                this->chromos[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[4]== 1){
                this->chromos[index].point++;
            }
        }
        if(max_index == 3){
            if(FullMaps[i].map[6]== -1){
                this->chromos[index].step--;
                #ifdef BREAK
                    break;
                #endif    
            }
            if(FullMaps[i].map[6]== 1){
                this->chromos[index].point++;
            }
        }

        
        
        i++;
    } while (i<FullMaps.size());
    
}