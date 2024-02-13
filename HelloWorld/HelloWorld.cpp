#include <iostream>
#include <string>

int main(int argc, char** args){
    std::cout<<"Hello World"<<std::endl;
    std::cout<<"What is your name? ";
    std::string myName;
    std::cin>>myName;
    std::cout<<"You are "<<myName<<"."<<std::endl;
}