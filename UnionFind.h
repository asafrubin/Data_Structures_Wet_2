#ifndef IMAGEPIXEL_UNIONFIND_H
#define IMAGEPIXEL_UNIONFIND_H


template <class T>
class UFnode{
    T data;
    int key;
    int groupId;
    int groupSize;
    UFnode *parent;
    UFnode *group;

public:
    //UFnode() : data(), key(0), groupId(0), groupSize(0), parent(nullptr), group(nullptr) {}
    explicit UFnode(int key) : data(key), key(key), groupId(key), groupSize(1), parent(nullptr), group(nullptr) {}
    UFnode<T> *get_parent(){
        return parent;
    }
    int get_groupSize(){
        return groupSize;
    }
    int get_key(){
        return key;
    }
    void set_data(T data){
        if(!data)
            return;
        this->data = data;
    }
    T& get_data(){
        return this->data;
    }
    void set_parent(UFnode<T>* parent){
        this->parent = parent;
    }
    void set_groupSize(int size){
        groupSize = size;
    }
    void zero(){
        groupId = -1;
        groupSize = -1;
        group = nullptr;
    }

};

template <class T, typename GetKey>
class UnionFind {
    GetKey getKey;
    UFnode<T> **groups;
    UFnode<T> **elements;
    int size;

public:
    UnionFind() : groups(nullptr), elements(nullptr), size(0) {}
    ~UnionFind(){
        for(int i=0;i<size;i++){
            delete elements[i];
        }
        delete[] groups;
        delete[] elements;
        groups = nullptr;
        elements = nullptr;
    }

    void init(int size){
        this->size = size;
        groups = new UFnode<T>*[size];
        elements = new UFnode<T>*[size];

        for(int i=0; i<size; i++){
            elements[i] = new UFnode<T>(i);
            groups[i] = elements[i];
        }
    }
    void union_set(int p, int q){
        UFnode<T> *p_root = get_root(p);
        UFnode<T> *q_root = get_root(q);
        /*
        if(q_root == p_root){
            throw std::bad_typeid();
        }
        */
        if(p_root->get_groupSize() <= q_root->get_groupSize()){
            p_root->set_parent(q_root);
            int size = p_root->get_groupSize() + q_root->get_groupSize();
            q_root->set_groupSize(size);
            p_root->zero();
            return;
        }
        q_root->set_parent(p_root);
        int size = p_root->get_groupSize() + q_root->get_groupSize();
        p_root->set_groupSize(size);
        q_root->zero();
    }

    T* find(T data){
        int key = getKey(data);
        if(key >= size){
            return nullptr;
        }
        UFnode<T>* node = elements[key];
        if(!node->get_parent()){
            return &(elements[key]->get_data());
        }
        int group = find_aux(node);
        node->set_parent(elements[group]);

        return &(elements[group]->get_data());
    }

    int find_aux(UFnode<T> *node){
        if(!node->get_parent()){
            return node->get_key();
        }
        int key = find_aux(node->get_parent());
        node->set_parent(elements[key]);

        return key;
    }

    UFnode<T>* get_root(int key) {
        UFnode<T> *node = elements[key];

        while (node->get_parent()) {
            node = node->get_parent();
        }
        return node;
    }
};

#endif //IMAGEPIXEL_UNIONFIND_H
