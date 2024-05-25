#pragma once

#ifndef NODE_HEADER
#define NODE_HEADER

template <typename type>
class Node{
private:
    type value;
    Node * next = NULL;
    Node * previous = NULL;
public:
    // constructores y destructor
    Node()
    {

    }

    Node(type value) : value(value), next(NULL), previous(NULL) {}
    ~Node(){};

    // setter
    void setValue(type value){this->value = value;}
    void setNext(Node * next){this->next = next;}
    void setPrevious(Node * previous){this->previous = previous;}

    // getter
    type getValue(){return this->value;}
    Node * getNext(){return this->next;}
    Node * getPrevious(){return this->previous;}
    type * getPointerToValue(){return &this->value;}
};
#endif // NODE_HEADER
