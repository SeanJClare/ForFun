#include "Node.h"

Node::Node(string valToSet, Node* nodeToNext){
    value = valToSet;
    next = nodeToNext;
}
Node::Node(string valToSet){
    value = valToSet;
    next = nullptr;
}

void Node::setVal(string toSet)
{
    value = toSet;
}

string Node::getVal()
{
    return value;
}

void Node::setNext(Node* toSet)
{
    next = toSet;
}

Node* Node::getNext()
{
    return next;
}
