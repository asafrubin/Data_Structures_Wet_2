#ifndef LIST_LIST_H
#define LIST_LIST_H

#include "listNode.h"
#include <fstream>

template<class T>
class List{
private:
    int size;
    Node<T>* head;
    Node<T>* tail;

public:
    List() : size(0), head(new Node<T>), tail(head) {}
    ~List(){
        int counter = 0;
        //int a_size = this->size;
        if(size == 0){
            delete head;
            head = nullptr;
            return;
        }
        while(head->getNext() != nullptr){
            removeByPointer(head->getNext(), false);
            counter++;
        }
        //if(counter != a_size)
            //std::cout << "not matching!!!" << std::endl;
        delete head;
        head = nullptr;
    }
    List(List<T> const &list){
        Node<T>* it = list.getHead();
        while(it != nullptr){
            insert(it->getData());
            it = it->getNext();
        }
        size = list.size;
    }

    const Node<T>* insert(T data) {
            Node<T> *newNode = new(std::nothrow) Node<T>(data);
            if(newNode == nullptr) {
                return nullptr;
            }

            newNode->setNext(head->getNext());
            head->setNext(newNode);
            newNode->setPrevious(head);
            if(newNode->getNext() != nullptr){
                newNode->getNext()->setPrevious(newNode);
            }

            if(size == 0){
                tail = newNode;
            }
            //increase size of list by 1
            size++;
            return newNode;
        };
    Node<T>* find(T data) {
        Node<T>* it = head->getNext();
        while (it != nullptr) {
            if (*data == *it->getData()) {
                return it;
            }
            it = it->getNext();
        }
        return nullptr;
    }

    void remove(T data, int destroyFlag=0){
        Node<T>* nodeToRemove = find(data);
        if(nodeToRemove == nullptr) {
            return;
        }
        //case node to remove is at the end
        if(nodeToRemove == tail){
            nodeToRemove->getPrevious()->setNext(nullptr);
            tail = nodeToRemove->getPrevious();
            if(destroyFlag){
                delete nodeToRemove->getData();
            }
            delete nodeToRemove;
            //reduce size of list by 1
            size--;
            return;
        }
        //general case
        Node<T>* previous = nodeToRemove->getPrevious();
        previous->setNext(nodeToRemove->getNext());
        previous->getNext()->setPrevious(previous);

        if(destroyFlag){
            delete nodeToRemove->getData();
        }
        delete nodeToRemove;
        //reduce size of list by 1
        size--;
    }
    void removeByPointer(Node<T>* nodeToRemove, int destroyFlag){
        if(!nodeToRemove) {
            return;
        }
        remove(nodeToRemove->getData(), destroyFlag);
    }
    int getSize() const{
        return size;
    }
    Node<T>* getHead(){
        return head->getNext();
    }
    Node<T>* getTail(){
        if(size == 0){
            return nullptr;
        }
        return tail;
    }
    void destroy(){
        int counter = 0;
        //int a_size = this->size;
        if(size == 0){
            delete head;
            head = nullptr;
            return;
        }
        while(head->getNext() != nullptr){
            removeByPointer(head->getNext(), true);
            counter++;
        }
        //if(counter != a_size)
        //std::cout << "not matching!!!" << std::endl;
        delete head;
        head = nullptr;
    }
};

#endif //LIST_LIST_H
