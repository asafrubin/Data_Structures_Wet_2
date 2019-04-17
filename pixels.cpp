#include "Label.h"
#include "pixels.h"

void Pixel::set_pixel_id(int id) {
    pixelID = id;
}

int Pixel::get_pixel_id() {
    return pixelID;
}

void Pixel::set_max_label(Label labelID) {
    max_Label = labelID;
}

Label Pixel::get_max_label() {
    return max_Label;
}

void Pixel::setLabelScore(int labelID, int score) {
    Label label(labelID, score);

    labels_tree.remove(label);
    labels_tree.insert(label);

    max_Label = labels_tree.getRoot()->getSum();
}

void Pixel::resetLabel(int labelID) {
    Label label(labelID, 0);
    labels_tree.remove(label);
    if(labels_tree.getSize() != 0) {
        max_Label = labels_tree.getRoot()->getSum();
        return;
    }
    max_Label = Label();
}

Label Pixel::getHighestScoredLabel() {
    return max_Label;
}

bool Pixel::checkIfLabelExist(int label) {
    return labels_tree.find(Label(label)) != nullptr ;
}

bool Pixel::isLabeld() {
    return labels_tree.getSize() != 0;
}

void Pixel::merge2pixels(Pixel &pixel_1, Pixel &pixel_2) {
    labelCmp cmpFUNC;
    pixel_1.labels_tree.mergeTrees(pixel_2.labels_tree, cmpFUNC);
    /*
    AVLnode<Label,labelSumFunc>* root = pixel_2.labels_tree.getRoot();
    pixel_2.labels_tree.destroyTree(root);
    root = nullptr;
     */
    if(pixel_1.labels_tree.getSize() == 0){
        pixel_1.max_Label = Label(0,0);
        return;
    }
    Label max_label = pixel_1.labels_tree.getRoot()->getSum();
    pixel_1.max_Label = max_label;
}

Pixel::~Pixel() {}


