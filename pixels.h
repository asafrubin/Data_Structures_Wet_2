#ifndef IMAGEPIXEL_PIXELS_H
#define IMAGEPIXEL_PIXELS_H

#include "Label.h"
#include "AVLtree.h"
#include "AVLnode.h"

class labelSumFunc{
    Label max(Label &a, Label &b){
        if(a.get_score() < b.get_score())
            return b;
        else if(a.get_score() == b.get_score()){
            if(a.get_id() < b.get_id()){
                return b;
            }
            else
                return a;
        }
        return a;
    }
public:
    Label operator()(Label &label_1, Label &label_2, Label &label_3){
        Label max_label = max(label_2, label_3);
        return max(label_1, max_label);
    }
};
class labelCmp{
public:
    //this one is for merging 2 arrays
    Label operator()(Label &a, Label &b, int &i){
        return Label(a.get_id(), a.get_score() + b.get_score());
    }
    //this is for creating an array from a tree
    void operator()(AVLnode<Label, labelSumFunc> *node, Label *array, int *i){
        array[*i] = node->getData();
        (*i)++;
    }
    //this one is for comparing label id's
    int operator()(Label &label_1, Label &label_2){
        if( label_1.get_id() == label_2.get_id())
            return 0;
        else if(label_1.get_id() < label_2.get_id())
            return -1;
        else
            return 1;
    }
};

class Pixel {
    int pixelID;
    Label max_Label;
    AVLtree<Label, labelCmp, labelSumFunc> labels_tree;

public:
    explicit Pixel(int pixelID) : pixelID(pixelID), max_Label(0,0){}
    ~Pixel();
    void set_pixel_id(int id);
    int get_pixel_id();
    void set_max_label(Label label);
    Label get_max_label();
    void setLabelScore(int label, int score);
    void resetLabel(int label);
    Label getHighestScoredLabel();
    bool checkIfLabelExist(int label);
    bool isLabeld();
    static void merge2pixels(Pixel &pixel_1, Pixel &pixel_2);
};


#endif //IMAGEPIXEL_PIXELS_H
