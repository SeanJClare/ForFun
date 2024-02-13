#include <iostream>
#include <string>
int main(int argc, char *argv[]){
    std::string output;
   for(int i=1;i<=100;++i){
       output="";
    if(i%3==0){
        output+="Fizz";
    }
    if(i%5==0){
        output+="Buzz";
    }
    if(output.empty()){
        std::cout<<i<<std::endl;
    }else{
        std::cout<<output<<std::endl;
    }
   }
}