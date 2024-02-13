#include "Vertex.h"

Vertex::Vertex(char id){
    Vertex::id=id;
}

Vertex::Vertex(Vertex* initalAdd, char iden){
    connect(initalAdd);
    id=iden;
}

Vertex::~Vertex(){
    for(unsigned i=0;i<connections.size();++i){
        delete connections[i];
    }
    connections.clear();
}

void Vertex::connect(Vertex* toConnect){
    if(toConnect!=nullptr){
        connections.push_back(toConnect);
    }
}

bool Vertex::disconnect(Vertex* toRemove){
    bool removed = false;
     if(toRemove!=nullptr){
        for(unsigned i=0;i<connections.size()&&!removed;++i){
            if(toRemove==connections[i]){
                delete connections[i];
                connections[i]=nullptr;
                removed=!removed;
            }
        }
     }
     return removed;
}

std::string Vertex::toString(){
    std::string toRet = "Id: ";
    toRet+=id;
    toRet.append(", Connections: ");
    for(unsigned i=0;i<connections.size();++i){
        toRet.append(connections[i]->id+", ");
    }
    return toRet;
}