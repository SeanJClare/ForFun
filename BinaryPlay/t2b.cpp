#include <iostream>
#include <stdlib.h>
#include <bitset>
#include <vector>

using std::cout;
using std::endl;

int main(int argc, char** args){
    int maxChars=0;
    int charCount;
    std::vector<std::vector<std::bitset<8>>> bitsets;

    // Single Line

    /* Multi
     *
     * 
     * 
     * 
     * Line
    */ 

   //Spereates each argument given into characters
    if(argc>1){
        cout<<"Arguments Total: "<<argc-1<<endl<<endl;
        for(int i=1;i<argc;++i){
            charCount=0;
            while(args[i][charCount]!=0){
                ++charCount;
            }
            if(maxChars<charCount){
                maxChars=charCount;
            }
        }
        
        //For all arguments, add them to a binary vector (list)
        for(int i=1;i<argc;++i){
            charCount=0;
            std::vector<std::bitset<8>> toAdd;
            while(args[i][charCount]!=0){
                toAdd.push_back(std::bitset<8>(args[i][charCount]));
                ++charCount;
            }
            bitsets.push_back(toAdd);
            cout<<endl;
        }
        
    }
    
    cout<<"Text:"<<endl;
        for(int i=1;i<argc;++i){
            charCount=0;
            cout<<"Argument: "<<i<<endl;
            cout<<"Characters: "<<endl;
            while(args[i][charCount]!=0){
                cout<<'\''<<args[i][charCount]<<'\''<<' ';
                ++charCount;
            }
            cout<<endl;
        }
        cout<<endl<<"Largest charCount: "<<maxChars<<endl<<endl;
        
        cout<<"Binary:"<<endl;
        for(int i=1;i<argc;++i){
            charCount=0;
            cout<<"Argument: "<<i<<endl;
            while(args[i][charCount]!=0){
                cout<<bitsets[i-1][charCount]<<", ";
                ++charCount;
            }
            cout<<endl;
        }
}

