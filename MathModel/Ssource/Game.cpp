#include "../header/Game.h"




Game::Game(int n, int high, int width) {
    if (n * 4 > (high - 2)* (-2 + width))
    {
        std::cout << "Error (space)!\n";
        exit(1);
    }
    int stepX, stepY;
    stepX = 0;
    stepY = int((high - 2) / (n + 2));

    snake = new Snake[n];
    for (int i = 0; i < n; i++)
    {
        snake[i] = Snake(i, width / 2 /*(n + 1) + stepX * i*/, int(high / (n + 1)) + i * stepY);
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
        std::cin >> numofBorder;
        border = new int* [numofBorder];
        for (int i = 0; i < numofBorder; i++)
        {
            border[i] = new int[2];
            std::cout << "Enter coord x: \n";
            std::cin >> border[i][0];
            std::cout << "Enter coord y: \n";
            std::cin >> border[i][1];
            if (checkBorder(border[i][0], border[i][1]) || checkSnake(border[i][0], border[i][1]))
            {
                std::cout << "Error! This border can't be used!\n";
                delete[] border[i];
                i--;
            }
        }

        std::cout << "Complite!\n";
    }
    else
    {
        numofBorder = 0;
    }
    if ((width - 2) * (high - 2) > 100)
        numofFood = int((width - 2) * (high - 2) / 100);
    else
        numofFood = int(width * high / 10);
    food = new int* [numofFood];
    srand(time(NULL));
    for (int i = 0; i < numofFood; i++)
    {
        food[i] = new int[2];
        food[i][0] = rand() % (width - 2) + 1;//0 - Ox
        food[i][1] = rand() % (high - 2) + 1;//1 - Oy
        while (/*checkFood(food[i][0], food[i][1]) ||*/ checkBorder(food[i][0], food[i][1]) || checkSnake(food[i][0], food[i][1]))
        {
            food[i][0] = rand() % (width - 2) + 1;//0 - Ox
            food[i][1] = rand() % (high - 2) + 1;//1 - Oy         
        
        }

    }
    numofAlive = numofSnake;
    step.resize(n);
    for (int i = 0; i < step.size(); i++)
    {
        step[i] = 0;
    }
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

    snake = new Snake[n];
    for (int i = 0; i < n; i++)
    {
        snake[i]= Snake(i,width/(n+1)+stepX*i,high/(n+1)+i*stepY);
    }
    
    this->high=high;
    this->width=width;
    this->numofSnake=n;

    radius = r;
    scan = new int[r*r-1];
    char a;
       
    
    std::cout<<"Do u want add border?\n";
    std::cin>>a;
    if(a=='y'||a=='Y'){
        std::cout<<"How much?";
        std::cin>>numofBorder;
        border = new int*[numofBorder];
        for (int i = 0; i < numofBorder; i++)
        {
            border[i]=new int[2];
            std::cout<<"Enter coord x: \n";
            std::cin>>border[i][0];
            std::cout<<"Enter coord y: \n";
            std::cin>>border[i][1];
            if (checkBorder(border[i][0], border[i][1])||checkSnake(border[i][0], border[i][1]))
            {
                std::cout<<"Error! This border can't be used!\n";
                delete[] border[i];
                i--;
            }
        }
        
        std::cout<<"Complite!\n";
    }else
    {
        numofBorder=0;
    }
    if((width-2)*(high-2)>100)
        numofFood = (width-2)*(high-2)/20;
    else
        numofFood =width*high/10;
    food =new int*[numofFood];
    srand(time(NULL));
    for (int i = 0; i < numofFood; i++)
    {
        food[i]=new int[2];
        food[i][0]=rand()%(width-2)+1;//0 - Ox
        food[i][1]=rand()%(high -2)+1;//1 - Oy
        // if (checkFood(food[i][0],food[i][1]) &&checkBorder(food[i][0], food[i][1])&&checkSnake(food[i][0], food[i][1]))
        // {
        //    delete[] food[i]; 
        //    i--;
        //
        // }
        
    }   
    numofAlive = n;
    step.resize(n);
    for (int i = 0; i < step.size(); i++)
    {
        step[i] = 0;
    }
}


Game::~Game(){
    delete[] snake;
    if(radius>0)
    delete[] scan;
    if (numofBorder > 0) {
        for (int i = 0; i < numofBorder; i++)
        {
            delete[] border[i];
        }
   
        delete[] border;
    }

    for (int i = 0; i < numofFood; i++)
    {
        delete[] food[i];
    }
    delete[] food;
}

void Game::Logic(){
    if (numofAlive<=0)
    {
        std::cout<<"Game Over \nMax step = "<<step[0];
        
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
            if(checkBorder(snake[i].getTailX(0),snake[i].getTailY(0)))//|| checkEnemy(snake[i].getTailX(0),snake[i].getTailY(0),i))
            {
                 snake[i].setAlive();
                 numofAlive--;
            }else
            {
                
                step[i]++;
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

                for (int j = 0; j < numofFood; j++)
                {
                    if (food[j][0] == snake[i].getTailX(0) && food[j][1] == snake[i].getTailY(0))
                    {
                        generateCurrentFood(j);
                        break;
                    }
                }
                
                
                if(eat){
                    snake[i].setTailX(tmpX);
                    snake[i].setTailY(tmpY);
                    snake[i].setFullHungry();
                    snake[i].setBody();
                }
                snake[i].setHungry();
                
            }
        }
    }
}

void Game::Drow(){
    if (numofAlive > 0)
    {
        std::system("clear");
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
        for (int id = 0; id < step.size(); id++)
        {
            std::cout << "Step[" << id + 1 <<"]: " << step[id] << std::endl;
        }
    }
}


void Game::Input(std::vector<std::vector<int>> x){
    for (int i = 0; i < numofSnake; i++)
    {
        if(snake[i].getAlive()){
            for (int j = 0; j < x[i].size(); j++)
            {
                if (x[i][j] == 1) snake[i].setCourse(j);
            }
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

std::vector<int> Game::getScan(int num){
    int x = snake[num].getTailX(0);
    int y = snake[num].getTailY(0);
    std::vector<int> tmp;
    for (int i = 0; i < radius * 2 + 1; i++)
    {
        for (int j = 0; j < radius * 2 + 1; j++)
        {
            if (i == radius && j == radius) {
            
            }
            else
            {
                if (checkFood(x + j, y + i)) {
                    tmp.push_back(1);
                    tmp.push_back(0);
                    tmp.push_back(0);
                }
                else if (checkBorder(x + j, y + i) || checkEnemy(x + j, y + i, 0)) {
                    tmp.push_back(0);
                    tmp.push_back(0);
                    tmp.push_back(1);
                }
                else
                {
                    tmp.push_back(0);
                    tmp.push_back(1);
                    tmp.push_back(0);
                }
            }
        }
    }
    return tmp;
}


bool Game::checkBorder(int x, int y) {
    if (x <= 0 || y <= 0 || x >= width || y >= high) {
        return true;
    }
    for (int i = 0; i < numofBorder; i++)
    {
        if (x == border[i][0] && y == border[i][1])
            return true;
    }
    
    return false;
    
}

bool Game::checkFood(int x, int y){
    for (int i = 0; i < numofFood; i++)
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
        for (int j = 0; j < numofFood; j++)
        {
            Food << F[i][j][0]<<" "<<F[i][j][1]<<" ";
        }
        Food<<"\n";
    }
    
    
}

int Game::getNumAlive(){
    return numofAlive;
}



