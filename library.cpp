
#include <new>
#include "library.h"
#include "ImagePixel.h"

void *Init(int pixels) {
    if(pixels <= 0){
        return nullptr;
    }
    void* DS = new(std::nothrow) ImagePixel(pixels);
    return DS;
}

StatusType AddImage(void *DS, int imageID) {
    if(DS == nullptr) {
        return INVALID_INPUT;
    }

    return ((ImagePixel*)DS)->addImage(imageID);
}

StatusType DeleteImage(void *DS, int imageID) {
    if(DS == nullptr){
        return INVALID_INPUT;
    }

    return ((ImagePixel*)DS)->deleteImage(imageID);
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score) {
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return ((ImagePixel*)DS)->setLabelScore(imageID, pixel, label, score);
}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label) {
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return ((ImagePixel*)DS)->resetLabelScore(imageID, pixel, label);
}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label) {
    if(DS == nullptr || label == nullptr){
        return INVALID_INPUT;
    }
    return ((ImagePixel*)DS)->getHighestScoredLabel(imageID, pixel, label);
}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2) {
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    return ((ImagePixel*)DS)->mergeSuperPixels(imageID, pixel1, pixel2);
}

void Quit(void **DS) {
    if(DS == nullptr) {
        return;
    }
    delete (*((ImagePixel**)DS));
    *DS = nullptr;
}