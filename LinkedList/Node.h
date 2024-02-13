#include <string>
using std::string;

#ifndef NODE
class Node{
    public:
        Node(string toSet);
        Node(string valToSet, Node* nodeToNext);
        void setVal(string toSet);
        string getVal();
        void setNext(Node* toSet);
        Node* getNext();
    private:
    string value;
    Node* next;

};
#endif