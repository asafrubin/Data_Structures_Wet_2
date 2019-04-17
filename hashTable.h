#ifndef IMAGEPIXEL_HASHTABLE_H
#define IMAGEPIXEL_HASHTABLE_H

#include "List.h"
#include "listNode.h"

template<class T, class GetKey>
class hashTable {
    GetKey getKey;
    List<T> **table;
    int table_size;
    int cur_size;
public:
    explicit hashTable(int size) : table_size(size), cur_size(0){
        table = new List<T>*[size];
        for(int i=0;i<size;i++){
            table[i] = new List<T>;
        }
    }
    ~hashTable(){
        for(int i=0; i < table_size; i++){
            table[i]->destroy();
            delete table[i];
        }
        delete[] table;
    }
    T find(T data){
        int key = getKey(data);
        int hash = (key%table_size);

        if(table[hash]->getSize() == 0){
            return nullptr;
        }
        Node<T> *node = table[hash]->find(data);
        if(!node){
            return nullptr;
        }
        return node->getData();
    }

    bool insert(T data){
        int key = getKey(data);
        int hash = key % table_size;

        if(table[hash]->find(data)){
            return false;
        }
        table[hash]->insert(data);
        cur_size++;

        //resize 1 for double the array, 2 for divide array
        if(cur_size == table_size){
            resize(1);
        }
        return true;
    }

    bool remove(T data){
        int key = getKey(data);
        int hash = key % table_size;

        table[hash]->remove(data, true);

        if(cur_size <= (table_size/2) ){
            resize(2);
        }

        return true;
    }

    void resize(int option){
        int factor = 0;
        if( option == 1){
            factor = table_size*2;
        }
        else
            factor = (table_size / 2) + 1;
        List<T> **old_table = table;
        List<T> **new_table = new List<T>*[factor];
        for(int i=0;i<factor;i++){
            new_table[i] = new List<T>;
        }
        table = new_table;
        int old_table_size = table_size;
        table_size = factor;
        cur_size = 0;

        for(int i=0; i<old_table_size; i++){
            Node<T> *node = old_table[i]->getHead();
            while(node){
                insert(node->getData());
                node = node->getNext();
            }
        }
        for(int i=0;i<old_table_size;i++){
            delete old_table[i];
        }
        delete[] old_table;
    }
};

#endif //IMAGEPIXEL_HASHTABLE_H