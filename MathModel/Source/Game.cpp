#include "../Header/Game.hpp"




Game::Game(int n, int high, int width) {
    if (n * 4 > (high - 2)* (-2 + width))
    {
        std::cout << "Error (space)!\n";
        exit(1);
    }
    int stepX, stepY;
    stepX = 0;
    stepY = int((high - 2) / (n + 2));

    snake.resize(n);
    for (int i = 0; i < n; i++)
    {
        snake[i] = Snake( width / 2 /*(n + 1) + stepX * i*/, int(high / (n + 1)) + i * stepY);
    }

    this->high = high;
    this->width = width;
    this->numofSnake = n;

    radius = 0;
    char a;


    std::cout << "Do u want add border?\n";
    std::cin >> a;
    if (a == 'y' || a == 'Y') {
        std::cout << "How much?";
        int numofBorder;
        std::cin >> numofBorder;
        border.resize(numofBorder);
        for (int i = 0; i < numofBorder; i++)
        {
            border[i].resize(2);
            std::cout << "Enter coord x: \n";
            std::cin >> border[i][0];
            std::cout << "Enter coord y: \n";
            std::cin >> border[i][1];
            if (checkBorder(border[i][0], border[i][1]) || checkSnake(border[i][0], border[i][1]))
            {
                std::cout << "Error! This border can't be used!\n";
                i--;
            }
        }

        std::cout << "Complite!\n";
    }
    int numofFood;
    if ((width - 2) * (high - 2) > 100)
        numofFood = int((width - 2) * (high - 2) / 100);
    else
        numofFood = int(width * high / 10);
    food.resize(numofFood);
    srand(time(NULL));
    for (int i = 0; i < numofFood; i++)
    {
        food[i].resize(2);
        food[i][0] = rand() % (width - 2) + 1;//0 - Ox
        food[i][1] = rand() % (high - 2) + 1;//1 - Oy
        while (/*checkFood(food[i][0], food[i][1]) ||*/ checkBorder(food[i][0], food[i][1]) || checkSnake(food[i][0], food[i][1]))
        {
            food[i][0] = rand() % (width - 2) + 1;//0 - Ox
            food[i][1] = rand() % (high - 2) + 1;//1 - Oy         
        
        }

    }
    numofAlive = numofSnake;
}

Game::Game(int n, int r, int high, int width){
    if (n*4>(high-2)*(-2+width))
    {
        std::cout<<"Error (space)!\n";
        exit(1);
    }
    int stepX, stepY;
    stepX= 0;
    stepY=int((high-2)/(n+2));

    snake.resize(n);
    this->high=high;
    this->width=width;
    this->numofSnake=n;
    for (int i = 0; i < n; i++)
    {
        snake[i]= Snake(width/(n+1)+stepX*i,high/(n+1)+i*stepY);
        snake[i].setHungry(this->high*this->width*2);
    }
    


    radius = r;
    
    int numofFood = 10;
    food.resize(numofFood);
    srand(time(NULL));
    for (int i = 0; i < numofFood; i++)
    {
        food[i].resize(2);
        food[i][0]=rand()%(width-2)+1;//0 - Ox
        food[i][1]=rand()%(high -2)+1;//1 - Oy
       
    }   

    this->numofAlive = n;
 
}


Game::~Game(){

}

void Game::Logic(){
    if (numofAlive<=0)
    {
        std::cout<<"Game Over \nMax step = "<< this->getMaxStep();
        
        return;
    }
    else
    for (int i = 0; i < numofSnake; i++)
    {
        if(snake[i].getAlive())
        {
            switch (snake[i].getCourse())
            {
            case 0: snake[i].setMove(-1, 0);
                break;
            case 1: snake[i].setMove(0, -1);
                break;
            case 2: snake[i].setMove(1, 0);
                break;
            case 3: snake[i].setMove(0, 1);
                break;
            default:
                break;
            }
            if(checkBorder(snake[i].getTailX(0),snake[i].getTailY(0)) || checkEnemy(snake[i].getTailX(0),snake[i].getTailY(0),i) || this->snake[i].checkHeadTail())
            {
                 snake[i].setAlive();
                 numofAlive--;
            }else
            {
                snake[i].setStep();
                for (int j = 1; j < snake[i].getBody(); j++)
                {
                    if (snake[i].getTailX(0) == snake[i].getTailX(j) && snake[i].getTailY(0) == snake[i].getTailY(j))
                    {
                        snake[i].setAlive();
                        numofAlive--;
                    }
                }
                bool eat =false;
                int tmpX, tmpY;
                tmpX = snake[i].getTailX(snake[i].getBody() - 1);
                tmpY = snake[i].getTailY(snake[i].getBody() - 1);
                if(checkFood(snake[i].getTailX(	0),snake[i].getTailY(0)))
                { 
                    eat = true;
                    tmpX= snake[i].getTailX(snake[i].getBody()-1);
                    tmpY= snake[i].getTailY(snake[i].getBody()-1);

                }

                for (int j = 0; j < food.size(); j++)
                {

                    if (food[j][0] == snake[i].getTailX(0) && food[j][1] == snake[i].getTailY(0))
                    {
                        if(currentMode==Mode::Dinam){
                           generateCurrentFood(j);
                           break;
                        }else{
                            food.erase(food.begin()+j);
                        }
                    }
                }
                
                
                if(eat){
                    snake[i].setTail(tmpX, tmpY);
                    
                    snake[i].setHungry(this->high*this->width*2);
                }
                snake[i].setHungry();
                if (!snake[i].getAlive())
                    this->numofAlive--;
                
            }
        }
    }
}

void Game::Drow(){
    if (numofAlive > 0)
    {
        //std::system("clear");
        std::system("cls");
        std::cout << "This is Drow\n";
        //  std::system("cls");
        for (int i = 0; i < high; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == 0 || j == 0 || i == high - 1 || j == width - 1)
                {
                    std::cout << "#";
                }
                else if (checkBorder(j, i))
                {
                    std::cout << "#";
                }
                else if (checkSnake(j, i))
                {
                    for (int k = 0; k < numofSnake; k++)
                    {
                        if (snake[k].getAlive())
                        {
                            if (checkHead(j, i, k))
                            {
                                std::cout << "@";
                                break;
                            }
                            else {
                                std::cout << "o";
                                break;
                            }
                        }
                    }
                    //std::cout<<"o";
                }
                else  if (checkFood(j, i)) {
                    std::cout << "F";
                }
                else std::cout << " ";
            }
            std::cout << '\n';
        }

        std::vector<double> tmp;
        tmp = this->getScan(0);
        for (int i = 0; i < tmp.size(); i++)
        {
            std::cout << tmp[i] << " ";
        }

        for (int id = 0; id < snake.size(); id++)
        {
            std::cout << "Step[" << id  <<"]: " << snake[id].getStep() << std::endl;
            std::cout << "Hangry[" << id << "] = " << snake[id].getHungry() << std::endl;
            std::cout << "Alive[" << id << "] = " << snake[id].getAlive() << std::endl;
        }


    }  
}


void Game::Input(std::vector<std::vector<double>> x){
    for (int i = 0; i < numofSnake; i++)
    {
        if(snake[i].getAlive()){
            int max_index = 0;
            double max = x[i][0];
            for (int j = 0; j < x[i].size(); j++)
            {
                if (x[i][j] > max){
                    max = x[i][j];
                    max_index = j;
                }
                 
            }
            snake[i].setCourse(max_index);
        }
    }
    
}
void Game::Input(std::vector<int> x) {
    for (int i = 0; i < numofSnake; i++){
        if (snake[i].getAlive()) {
            snake[i].setCourse(x[i]);
        }

    }

}
//NEED UPGRADE THIS FUNCTION !!!
void Game::newFood(int num){
    do
    {
        food[num][0]=rand()%(width-2)+1;
        food[num][1]=rand()%(high-2)+1;
    } while (checkSnake(food[num][0],food[num][1])||checkFood(food[num][0],food[num][1])||checkBorder(food[num][0],food[num][1]));
    
}

void Game::generateCurrentFood(int index) {
    do
    {
        food[index][0] = rand() % (width - 2) + 1;
        food[index][1] = rand() % (high - 2) + 1;
    } while (!checkSnake(food[index][0], food[index][1]) && !checkBorder(food[index][0], food[index][1]));
    
}

std::vector<double> Game::getScan(int num){
    int x = snake[num].getTailX(0);
    int y = snake[num].getTailY(0);
    int count =0 ;
    std::vector<double> tmp;
    #ifndef TREATMENT
        tmp.resize((pow((radius)*2+1,2)-1));
        for (int i = -radius; i <= radius; i++)
        {
            for (int j = -radius; j <= radius; j++)
            {
                if (i == 0 && j == 0) {
                
                }
                else
                {
                    if (checkBorder(x + j, y + i) || checkEnemy(x + j, y + i, num)) {
                        tmp[count]= -1;
                    }else if (checkFood(x + j, y + i)) {
                        tmp[count]=1;
                    }else{
                        tmp[count]=0;
                    }
                    count++;
                }
            }
        }
    #endif
    #ifdef TREATMENT
        tmp.resize(2*(pow((radius)*2+1,2)-1));
        for (int i = -radius; i <= radius; i++)
        {
            for (int j = -radius; j <= radius; j++)
            {
                if (i == 0 && j == 0) {
                
                }
                else
                {
                    if (checkBorder(x + j, y + i) || checkEnemy(x + j, y + i, num)) {
                        tmp[count]= 1;
                        
                    }else{
                        tmp[count]= 0;

                    }
                    if (checkFood(x + j, y + i)) {
                        tmp[count+tmp.size()/2]=1;
                    }else{
                        tmp[count+tmp.size()/2]=0;
                    }
                    count++;
                }
            }
        }
    #endif
    return tmp;
}


bool Game::checkBorder(int x, int y) {
    if (x <= 0 || y <= 0 || x >= width-1 || y >= high-1) {
        return true;
    }
    for (int i = 0; i < border.size(); i++)
    {
        if (x == border[i][0] && y == border[i][1])
            return true;
    }
    
    return false;
    
}

bool Game::checkFood(int x, int y){
    for (int i = 0; i < food.size(); i++)
    {
        if (food[i][0]==x&&food[i][1]==y)
        {
            return true;
        }
    }
    return false;
}

bool Game::checkSnake(int x, int y){
    for (int i = 0; i < numofSnake; i++)
    {
        if (snake[i].getAlive())
        {
            for (int j = 0; j < snake[i].getBody(); j++)
            {
                if(snake[i].getTailX(j)==x && snake[i].getTailY(j)==y){
                    return true;
                }
            }
        }
        
    }
    return false;
}

bool Game::checkEnemy(int x, int y , int num){
    for (int i = 0; i < numofSnake; i++)
    {
        if (i != num)
        {
            if (snake[i].getAlive())
            {
                for (int j = 0; j < snake[i].getBody(); j++)
                {
                    if (snake[i].getTailX(j) == x && snake[i].getTailY(j) == y) {
                        return true;
                    }
                }
            }

        }
        else {
            for (int j = 1; j < snake[num].getBody(); j++)
            {
                    if (snake[i].getTailX(j) == x && snake[i].getTailY(j) == y) {
                        return true;
                    }
            }
            
        }

    }
    return false;
    
}

bool Game::checkHead(int x, int y, int num){
    if (snake[num].getTailY(0)==y&&snake[num].getTailX(0)==x)
    {
        return true;
    }else
    {
        return  false;
    }    
}

/*void Game::stady(){
    for (int i = 0; i < numofFood; i++)
    {
        food[i][0]=rand()%(width-2)+1;
        food[i][1]=rand()%(high -2)+1;
    }
    
    std::vector<int*> rr;
    std::vector<int**> F;
    std::vector<std::vector<int>> scanData;
    std::vector<int> inp;
    inp.resize(numofSnake);
    char a;
    
    do
    {
    //  std::vector<int> inp;
        // Logic();
        std::cout<<"Before Drow\n";
        Drow();
        std::cout<<"\n\n";
        scanData.push_back(Scan(0));
        int k =0;
        
        for (int i = -radius; i <= radius; i++)
        {
            for (int j = -radius; j <= radius; j++)
            {
                if (i==0&&j==0)
                {
                    std::cout<<"@";
                }else if (scanData[scanData.size()-1][k]==0)
                {
                    std::cout<<"0";
                    k++;
                }else if(scanData[scanData.size()-1][k]==1)
                {
                    std::cout<<"F";
                    k++;
                }else
                {
                    std::cout<<"#";
                    k++;
                }
            }
            std::cout<<std::endl;
        }
      
        // a = std::getchar();
        std::cin>>a;
       
        switch (a)
        {
        case 'A':case 'a':{
            int tmp[4] = {1,0,0,0};
            rr.push_back(tmp);
            inp[0]=0;
            Input(inp);
        }
            break;
        case 'W':case 'w':
        {
            int tmp[4] = {0,1,0,0};
            rr.push_back(tmp);
            inp[0]=1;
            Input(inp);
        }
            break;
        case 'D':case 'd':
         {

            int tmp[4] = {0,0,1,0};
            rr.push_back(tmp);
            inp[0]=2;
            Input(inp);
            break;
         }
        case 'S':case 's':
        {
            int tmp[4] = {0,0,0,1};
            rr.push_back(tmp);
            inp[0]=3;
            Input(inp);
            break;
        }
        default:
            break;
        }

        std::cout<<"After switch\n";
        
        
        F.push_back(food);
        Logic();
        std::cout<<"After Logic\n";
    } while (a!='q');
    SaveGame(rr,F, scanData);
}
*/
//Finish this function (delete replay step in rr and F)
void Game::SaveGame(std::vector<int*> rr, std::vector<int**> F, std::vector<std::vector<int>> scanData){
    std::string fileNameRR;
    std::string fileNameInput;
    std::string fileNameFood;
    if (radius<5)
    {
        fileNameRR = "../Trening/radius"+std::to_string(radius)+"RR.txt";
        fileNameInput = "../Trening/radius"+std::to_string(radius)+"Input.txt";
        fileNameFood = "../Trening/radius"+std::to_string(radius)+"Food.txt";
    }else
    {
        fileNameRR = "../radius"+std::to_string(5)+"RR.txt";
        fileNameInput = "../radius"+std::to_string(5)+"Input.txt";
        fileNameFood = "../radius"+std::to_string(5)+"Food.txt";
    }
    std::fstream RR, Input, Food;
    RR.open(fileNameRR,std::fstream::in |std::fstream::out| std::fstream::in);
    Input.open(fileNameInput, std::fstream::in |std::fstream::out| std::fstream::in);
    Food.open(fileNameFood, std::fstream::in | std::fstream::out| std::fstream::in);
    for (int i = 0; i < scanData.size(); i++)
    {   
        for (int j = 0; j < i; j++)
        {
            if(scanData[i]==scanData[j]){
                scanData.erase(scanData.begin()+j);
                rr.erase(rr.begin()+j);
                F.erase(F.begin()+j);
            }
        }
    }
    for (int i = 0; i < scanData.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            RR<<rr[i][j]<<" ";
        }
        RR<<"\n";
        for (int j = 0; j < scanData[i].size(); j++)
        {
            Input<<scanData[i][j]<<" ";
        }
        Input<<"\n";
        for (int j = 0; j < food.size(); j++)
        {
            Food << F[i][j][0]<<" "<<F[i][j][1]<<" ";
        }
        Food<<"\n";
    }
    
    
}

int Game::getNumAlive(){
    return numofAlive;
}


 int Game::getMaxStep(){
     int max = 0;
     for (int i = 0; i < this->snake.size(); i++)
     {
         if(snake[i].getStep()>max) max = snake[i].getStep();
     }
     return max;
 }

void Game::emptyMap(){
    food.clear();
    border.clear();
}

void Game::setNumofBorderRand(int num){
    border.resize( num);
    bool tmp = false;
    for (int i = 0; i < num; i++)
    {
        tmp = false;
        border[i].resize(2);
        border[i][0] = rand()%(high-2)+1;
        border[i][1] = rand()%(width-2)+1; 
        for (int j = 0; j < i; j++)
        {
            if(border[i][0]==border[j][0] && border[i][1]==border[j][1])
            {
                tmp= true;
                break;
            }
        }
        if(tmp){
            i--;
            continue;
        }
        if (checkSnake(border[i][0], border[i][1]))
        {
            std::cout<<"Error! This border can't be used!\n";
            i--;
        }
    }
    
}

void Game::setMode(Mode m){
    this->currentMode = m;
}

void Game::setFood(std::vector<std::vector<int>> coord){
    this->food = coord;
}

int Game::getPoint(int i){
    return this->snake[i].getPoint();
}

int Game::getStep(int i ){
    return this->snake[i].getStep();
}