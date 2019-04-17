#include "ImagePixel.h"
#include "Image.h"


ImagePixel::ImagePixel(int pixels) : pixels(pixels), Table(hashTable<Image*,ImageIDkey>(100)) {}


StatusType ImagePixel::addImage(int imageID) {
    if(imageID <= 0){
        return INVALID_INPUT;
    }
    if(image_exists(imageID)){
        return FAILURE;
    }
    Image *image = new Image(imageID, pixels);
    Table.insert(image);

    return SUCCESS;
}

StatusType ImagePixel::deleteImage(int imageID) {
    if(imageID <= 0){
        return INVALID_INPUT;
    }
    if(!image_exists(imageID)){
        return FAILURE;
    }
    Image image(imageID);
    Table.remove(&image);

    return SUCCESS;
}

StatusType ImagePixel::setLabelScore(int imageID, int pixel, int label, int score) {
    if(pixel < 0 || pixel >= pixels || imageID <= 0 || label <= 0 || score <= 0){
        return INVALID_INPUT;
    }
    if(!image_exists(imageID)){
        return FAILURE;
    }

    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    image->setLabelScore(pixel, label, score);

    return SUCCESS;
}

StatusType ImagePixel::resetLabelScore(int imageID, int pixel, int label) {
    if(pixel < 0 || pixel >= pixels || imageID <= 0 || label <= 0){
        return INVALID_INPUT;
    }
    if(!image_exists(imageID) || !label_exists(imageID, pixel, label)){
        return FAILURE;
    }
    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    image->resetLabelScore(pixel, label);
    return SUCCESS;
}

StatusType ImagePixel::getHighestScoredLabel(int imageID, int pixel, int *label) {
    if(pixel < 0 || pixel >= pixels || imageID <= 0){
        return INVALID_INPUT;
    }
    if(!image_exists(imageID) || !is_labeled(imageID, pixel)){
        return FAILURE;
    }

    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    image->getHighestScoredLabel(pixel, label);

    return SUCCESS;
}

StatusType ImagePixel::mergeSuperPixels(int imageID, int pixel1, int pixel2) {
    if(pixel1 < 0 || pixel1 >= pixels || pixel2 < 0 || pixel2 >= pixels || imageID <= 0){
        return INVALID_INPUT;
    }
    if(!image_exists(imageID) || in_same_super_pixel(imageID, pixel1, pixel2)){
        return FAILURE;
    }

    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    image->mergeSuperPixels(pixel1, pixel2);

    return SUCCESS;
}

ImagePixel::~ImagePixel() {}

bool ImagePixel::image_exists(int imageID) {

    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    if(!image)
        return false;
    return true;
}

bool ImagePixel::label_exists(int imageID, int pixel, int label) {
    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    if(!image)
        return false;
    return image->checkIfLabelExist(pixel, label);
}

bool ImagePixel::is_labeled(int imageID, int pixel) {
    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    if(!image)
        return false;
    return image->checkIfLabeled(pixel);
}

bool ImagePixel::in_same_super_pixel(int imageID, int pixel1, int pixel2) {
    Image image_to_find(imageID);
    Image *image = Table.find(&image_to_find);
    if(!image)
        return false;

    return image->in_same_super_pixel(pixel1, pixel2);
}
