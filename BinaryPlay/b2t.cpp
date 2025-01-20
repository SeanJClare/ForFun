#include <iostream>
#include <stdlib.h>
#include <bitset>
#include <vector>

using std::cout;
using std::endl;

int main(int argc, char** args){
    std::vector<std::bitset<8>> bitsets;
    std::string output;

    if(argc>1){
        cout<<"Arguments Total: "<<argc-1<<endl<<endl;
        bitsets.reserve(argc-1);
        std::bitset<8> curr;
        for(int i=1;i<argc;++i){
            curr = std::bitset<8>(args[i]);
            bitsets.push_back(curr);
        }
    }

    cout<<"Characters:"<<endl;
    for(int i=0;i<bitsets.size();++i){
        char current=0;
        cout<<"'";
        current = bitsets[i].to_ulong();
        cout<<current;
        cout<<"', ";
    }
    cout<<endl;

    cout<<"String:"<<endl;
    for(int i=0;i<bitsets.size();++i){
        char current=0;
        current = bitsets[i].to_ulong();
        cout<<current;
    }
    cout<<endl;

    }