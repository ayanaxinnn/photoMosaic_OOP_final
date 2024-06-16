#include "image.h"
Data_Loader Image::im;
Image::Image(int _width, int _height) : width(_width), height(_height){} //Data_Loader 有爭議

Image::~Image() {}

int Image::get_width() { //回傳private variable
    return width;
}

int Image::get_height() { //同上
    return height;
}

