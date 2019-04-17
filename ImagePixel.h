#ifndef IMAGEPIXEL_IMAGEPIXEL_H
#define IMAGEPIXEL_IMAGEPIXEL_H

#include "library.h"
#include "hashTable.h"
#include "Image.h"

class ImageIDkey{
public:
    int operator()(Image *image){
        if(!image)
            return 0;
        return image->get_ImageID();
    }
};

class ImagePixel {
    int pixels;
    hashTable<Image*,ImageIDkey> Table;

    bool image_exists(int imageID);
    bool label_exists(int imageID, int pixel, int label);
    bool is_labeled(int imageID, int pixel);
    bool in_same_super_pixel(int imageID, int pixel1, int pixel2);
public:
    explicit ImagePixel(int pixels);
    ~ImagePixel();
    StatusType addImage(int imageID);
    StatusType deleteImage(int imageID);
    StatusType setLabelScore(int imageID, int pixel, int label, int score);
    StatusType resetLabelScore(int imageID, int pixel, int label);
    StatusType getHighestScoredLabel(int imageID, int pixel, int *label);
    StatusType mergeSuperPixels(int imageID, int pixel1, int pixel2);
};


#endif //IMAGEPIXEL_IMAGEPIXEL_H
