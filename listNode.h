#ifndef LIST_LISTNODE_H
#define LIST_LISTNODE_H

#include <iostream>

template <class T>
class Node{
    Node *previous;
    Node *next;
    T data;

public:
    Node() : previous(nullptr), next(nullptr), data(nullptr) {};
    explicit Node(T& data) : previous(nullptr),next(nullptr), data(data) {};
    virtual ~Node() {};
    Node(const Node& node){
        previous = node.previous;
        next = node.next;
        data = node.data;
    };
    T& getData(){
        return data;
    }
    void setData(T data){
        this->data = data;
    }
    void setNext(Node* next){
        this->next = next;
    }
    void setPrevious(Node* previous){
        this->previous = previous;
    }
    Node* getNext(){
        return next;
    }
    Node* getPrevious(){
        return previous;
    }
};

#endif //LIST_LISTNODE_H
