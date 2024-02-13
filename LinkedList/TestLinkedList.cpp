#include "LinkedList.h"
#include <iostream>
using std::cout;
using std::endl;

int main(int varc, char** argv){

    LinkedList* myLL = new LinkedList();

    const int numToAdd = 26;        // Number of nodes to add
    const string valueToFind = "d"; // Value of node to find
    const int indexToFind = 9;      // Index of node to find
    const int indexToDel = 7;       // Index of node to delete
    const string valueToDel = "m";  // Value of node to delete
                                    // Node values and indexes don't need to exist in list
    cout<<endl;

    //Test adding nodes
    
    string alphabet[26] {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    
    cout<<"Adding "<<numToAdd<<" nodes."<<endl;
    for(int i=0;i<numToAdd;++i){
        myLL->addNode(new Node((alphabet[i])));
    }
    cout<<myLL->toString();
    
    cout<<endl;

    //Test finding nodes
    cout<<"Testing finding of value: "<<valueToFind<<", Node found: "<<myLL->getNode(valueToFind)->getVal()<<endl;
    cout<<"Testing finding of index: "<<indexToFind<<", Node Found: "<<myLL->getNode(indexToFind)->getVal()<<endl;

    cout<<endl;

    //Test deleting nodes
    cout<<"Testing deletion of index: "<<indexToDel<<", Result: "<<myLL->deleteNode(indexToDel)<<endl;
    cout<<myLL->toString();
    cout<<"Testing deletion of value: "<<valueToDel<<", Result: "<<myLL->deleteNode(valueToDel)<<endl;
    cout<<myLL->toString();

    cout<<endl;

    //Test reversing list
    cout<<"Testing reversing list"<<endl;
    myLL->reverseList();
    cout<<myLL->toString();

    delete myLL;

 return EXIT_SUCCESS;   
}