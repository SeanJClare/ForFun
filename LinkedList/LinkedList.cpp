#include "LinkedList.h"

LinkedList::LinkedList(){
    size=0;
    head=nullptr;
}

LinkedList::~LinkedList(){
    Node* toDel = head;
    Node* nextToDel = nullptr;
    while(toDel!=nullptr){
        nextToDel = toDel->getNext();
        delete toDel;
        toDel=nextToDel;
    }
    head=nullptr;
}

Node* LinkedList::getNode(int indexToGet){
    Node* toCheck = head;
    int index = 0;
    while(index<indexToGet&&toCheck!=nullptr){
        toCheck=toCheck->getNext();
        ++index;
    }
    return toCheck;
}
Node* LinkedList::getNode(string valueToGet){
    Node* toCheck = head;
    if(toCheck==nullptr){
        return nullptr;
    }
    while(toCheck!=nullptr&&toCheck->getVal()!=valueToGet){
        toCheck=toCheck->getNext();
    }

    return toCheck;
}


void LinkedList::addNode(Node* toAdd){
    if(head==nullptr){
        head = toAdd;
    }else{
        getLastNode()->setNext(toAdd);
    }
    ++size;
}


bool LinkedList::deleteNode(string valToFind){
    bool success = false;
    if(head==nullptr){
        return success;
    }
    Node* toCheck = head;
    Node* previous = nullptr;
    
    if(toCheck->getVal()==valToFind){ // Move head
        head = toCheck->getNext();
        delete toCheck;
        success = true;
    }
    
    do{
        previous = toCheck;
        toCheck = toCheck->getNext();
        if(toCheck->getVal()==valToFind){
            previous->setNext(toCheck->getNext());
            delete toCheck;
            success = true;
        }
    }while(!success&&toCheck->getNext()!=nullptr);
    
    if(success){
        --size;
    }
    return success;
}

bool LinkedList::deleteNode(int indexToDel){
    bool success = false;
    if(head==nullptr||indexToDel<0){
        return success;
    }
    Node* toCheck = head;
    Node* previous = nullptr;

    int index=0;
    if(indexToDel==0){
        head = toCheck->getNext();
        delete toCheck;
        success = true;
    }else{
        while(index<indexToDel&&toCheck!=nullptr){
            previous = toCheck;
            toCheck = toCheck->getNext();
            ++index;
        }
        if(index==indexToDel&&toCheck!=nullptr){    // Might be at end index
            previous->setNext(toCheck->getNext());
            delete toCheck;
            success = true;
        }
    }   

    if(success){
        --size;
    }

    return success;
}

void LinkedList::reverseList(){
    if(head==nullptr){
        return;
    }

    Node* previous = nullptr;
    Node* current = head;
    Node* next = current->getNext();
    

    current->setNext(nullptr);

    while(next!=nullptr){
        previous = current;
        current = next;
        next=current->getNext();
        current->setNext(previous);
        
    }

    head = current;
}

Node* LinkedList::getLastNode(){
    Node* current = head;
    while(current->getNext()!=nullptr){
        current = current->getNext();
    }
    return current;
}

string LinkedList::toString()
{
    string toReturn="LinkedList size: "+std::to_string(getSize());
    toReturn+="\nNodes: ";
    Node* currentNode = head;
    while(currentNode!=nullptr){
        toReturn+=currentNode->getVal()+"->";
        currentNode=currentNode->getNext();
    }
    toReturn+="null\n";

    return toReturn;
}

int LinkedList::getSize()
{
    return size;
}