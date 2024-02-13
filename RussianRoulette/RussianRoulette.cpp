#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <Windows.h>
// #include <pisstaker>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int inputInt();

int main(int argc, char **argv){
    
    // Get loaded chamber
    uint seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> cartridge (1, 6);
    int chamber = cartridge(generator);

    int choice = -1;
    // Get chosen chamber
    if(argc==1){
        // choice = inputInt();
        choice = cartridge(generator);
    }else{
        try{
            string intIn = argv[1];
            choice = stoi(intIn);
            if(choice<1||choice>6){
                choice = cartridge(generator);
            }
        }
        catch(std::exception e){
            choice = cartridge(generator);
        }
    }
    
    if(chamber==choice){
        cout<<"*BANG*"<<endl;
        // that tfw when to scare... T_T
        // remove("C:\Windows\System32");
    }else{
        cout<<"*click*"<<endl;
    }

}

int inputInt(){
    int ret;
    bool isError=true;
    do{
        std::cout<<"Choose a number (1-6): ";
        if (cin>>ret&&ret>0&&ret<7){
            isError=false;
        }else{
            cin.clear();
            cin.ignore(1,'\n');
        }                
    } while(isError);
    return ret;
}