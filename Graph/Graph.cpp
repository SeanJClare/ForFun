#include "Vertex.h"
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
int main(){
    
    std::string alphStr = "abcdefghijklmnopqrstuvwxyz";
    const char* alphArr = alphStr.c_str();

    std::vector<Vertex*> graph;
    // graph.reserve(9);
    graph.push_back(new Vertex('a'));
    for(unsigned i=1;i<8;++i){
        // cout<<alphArr[i]<<endl;
        graph.push_back(new Vertex(graph[i-1],alphArr[i]));
    }
    // for(unsigned i=1;i<10;++i){
    //     cout<<graph[i]->toString()<<endl;
    // }
    
    for(unsigned i=graph.size();i>=0;--i){
        cout<<graph[i]->toString()<<endl;
        delete graph[i];
    }
    delete alphArr;
    return EXIT_SUCCESS;
}