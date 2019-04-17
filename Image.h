#ifndef IMAGEPIXEL_IMAGE_H
#define IMAGEPIXEL_IMAGE_H

#include "pixels.h"
#include "UnionFind.h"
#include "AVLtree.h"
#include "AVLnode.h"

class getPixelKey{
public:
    int operator()(Pixel& pixel){
        return pixel.get_pixel_id();
    }
};
class Image {
    int imageID;
    UnionFind<Pixel, getPixelKey> *pixels;

public:
    Image();
    ~Image();
    explicit Image(int imageID);
    Image(int imageID, int pixels);
    void set_imageID(int imageID);
    void setLabelScore(int pixel,int label,int score);
    void resetLabelScore(int pixel,int label);
    void getHighestScoredLabel(int pixel,int *label);
    void mergeSuperPixels(int pixel1,int pixel2);
    bool checkIfLabelExist(int pixel,int label);
    bool checkIfLabeled(int pixel);
    bool in_same_super_pixel(int pixel1, int pixel2);
    bool operator==(Image &image);
    int get_ImageID();
};


#endif //IMAGEPIXEL_IMAGE_H
