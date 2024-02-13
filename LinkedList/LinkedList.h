#ifndef LinkedList
#include "Node.h"

class LinkedList{
    public:
    LinkedList();
    ~LinkedList();
    Node* getNode(int indexToGet);
    Node* getNode(string valueToGet);

    void addNode(Node* toAdd);
    bool deleteNode(string valToFind);
    bool deleteNode(int indexToDel);
    string toString();
    int getSize();

    void reverseList();
    private:
    Node* getLastNode();

    int size;
    Node* head;

};
#endif