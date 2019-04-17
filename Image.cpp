#include "Image.h"
#include "pixels.h"
#include "UnionFind.h"
#include "AVLtree.h"
#include "AVLnode.h"


//empty constructor
Image::Image() : imageID(0), pixels(nullptr) {}

//constructor for searching in data structues
Image::Image(int imageID)  : imageID(imageID), pixels(nullptr){}

//construcor to create real object
Image::Image(int imageID, int pixels) : imageID(imageID), pixels(new UnionFind<Pixel, getPixelKey>()) {
    this->pixels->init(pixels);
}

Image::~Image() {
    delete pixels;
}

void Image::set_imageID(int imageID) {
    this->imageID = imageID;
}

int Image::get_ImageID() {
    return imageID;
}

bool Image::operator==(Image &image) {
        return this->get_ImageID() == image.get_ImageID();
}

void Image::setLabelScore(int pixel, int label, int score) {
   Pixel *pixel_to_set = pixels->find(Pixel(pixel));

   pixel_to_set->setLabelScore(label, score);
}

void Image::resetLabelScore(int pixel, int label) {
    Pixel *pixel_to_set = pixels->find(Pixel(pixel));

    pixel_to_set->resetLabel(label);
}

void Image::getHighestScoredLabel(int pixel, int *label) {
    Pixel *pixel_to = pixels->find(Pixel(pixel));

    Label label1 = pixel_to->getHighestScoredLabel();
    *label = label1.get_id();
}

void Image::mergeSuperPixels(int pixel1, int pixel2) {
    Pixel *pixel_to_set1 = pixels->find(Pixel(pixel1));
    Pixel *pixel_to_set2 = pixels->find(Pixel(pixel2));

    this->pixels->union_set(pixel1, pixel2);
    int new_group = pixels->find(Pixel(pixel1))->get_pixel_id();
    if(new_group == pixel_to_set1->get_pixel_id()){
        Pixel::merge2pixels(*pixel_to_set1, *pixel_to_set2);
    } else
        Pixel::merge2pixels(*pixel_to_set2, *pixel_to_set1);
}

bool Image::checkIfLabelExist(int pixel, int label) {
    Pixel *p_pixel = pixels->find(Pixel(pixel));
    if(!p_pixel)
        return false;
    return p_pixel->checkIfLabelExist(label);
}

bool Image::checkIfLabeled(int pixel) {
    Pixel *p_pixel = pixels->find(Pixel(pixel));
    return p_pixel->isLabeld();
}

bool Image::in_same_super_pixel(int pixel1, int pixel2) {
   return pixels->find(Pixel(pixel1))->get_pixel_id() == pixels->find(Pixel(pixel2))->get_pixel_id();
}