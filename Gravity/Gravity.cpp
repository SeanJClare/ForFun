#include "Gravity.h"
#include <iostream>
#include <random>
#include <chrono>

using std::cout;
using std::endl;

int main(int argc, char** args){
    Gravity* test1 = new Gravity(10, '.', '@');
    // test1->toString();
    test1->populate(15);
    test1->iterate(9);
    delete test1;
}

Gravity::Gravity(int size, char particleEmpty, char particleChar){
    Gravity::ENV_SIZE=size;
    Gravity::PARTICLE_EMPTY = particleEmpty;
    Gravity::PARTICLE_CHAR=particleChar;
    enviroment = new char*[ENV_SIZE];
    for(int i=0;i<ENV_SIZE;++i){
        enviroment[i] = new char[ENV_SIZE]{};
        for(int n=0;n<ENV_SIZE;++n){
            enviroment[i][n]=PARTICLE_EMPTY;
        }
    }
}

Gravity::~Gravity(){
    for(int i=0;i<ENV_SIZE;++i){
        delete[] enviroment[i];
    }
    delete[] enviroment;
}

void Gravity::drop(int row, int col){
    if(col<ENV_SIZE && row<ENV_SIZE){
        enviroment[row][col] = PARTICLE_CHAR;
    }
}

void Gravity::populate(int numParticles){
    // Epoch time seed
    uint seed = std::chrono::system_clock::now().time_since_epoch().count();
    populate(seed, numParticles);
}

void Gravity::populate(int seed, int numParticles){
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> randPos(0, ENV_SIZE-1);
    int partCount=0;
    while(partCount<numParticles){
        int row = randPos(generator);
        int col = randPos(generator);
        if(enviroment[row][col]==PARTICLE_EMPTY){
            drop(row, col);
            ++partCount;
        }
    }
}

void Gravity::remove(int row, int col){
    if(col<ENV_SIZE && row<ENV_SIZE){
        enviroment[row][col] = PARTICLE_EMPTY;
    }
}

void Gravity::updateParticle(int row, int col){
    if(row<ENV_SIZE-1){   // Ensure somewhere to go

        if(enviroment[row+ENV_DOWN][col]==PARTICLE_EMPTY){ // Fall down if no particle down
            remove(row, col);
            drop(row+ENV_DOWN,col);
        }else if(col>0&&enviroment[row+ENV_DOWN][col+ENV_LEFT]==PARTICLE_EMPTY){ // Fall down left
            remove(row, col);
            drop(row+ENV_DOWN,col+ENV_LEFT);
        }else if(col<ENV_SIZE-1&&enviroment[row+ENV_DOWN][col-ENV_LEFT]==PARTICLE_EMPTY){ // Fall down right
            remove(row, col);
            drop(row+ENV_DOWN,col-ENV_LEFT);
        }   // Else remain in position
    }
}

// iterate from bottom up
void Gravity::iterate(int iterCount){
    
    for(int iter=0;iter<iterCount;++iter){        
        for(int row=ENV_SIZE-1;row>=0;--row){
            for(int col=ENV_SIZE-1;col>=0;--col){
                if(enviroment[row][col]==PARTICLE_CHAR){
                    updateParticle(row,col);
                }
            }
        }
        printEnv();
    }
}

void Gravity::printEnv(){
    int row;
    cout<<endl;
    for(row=0;row<ENV_SIZE;++row){
        
        cout<<row<<':'<<'|';
        for(int col=0;col<ENV_SIZE;++col){
            cout<<enviroment[row][col];
        }
        cout<<'|'<<endl;
    }
}

void Gravity::toString(){
    cout<<"Size: "<<ENV_SIZE<<endl;
    cout<<"Particle Empty: \'"<<PARTICLE_EMPTY<<'\''<<endl;
    cout<<"particle Character: \'"<<PARTICLE_CHAR<<'\''<<endl;
    cout<<"ENV_DOWN: "<<ENV_DOWN<<endl;
    cout<<"ENV_LEFT: "<<ENV_LEFT<<endl;
}

