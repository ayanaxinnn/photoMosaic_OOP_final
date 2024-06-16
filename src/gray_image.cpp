#include "gray_image.h"

GrayImage::GrayImage() : Image(0,0), pixels(nullptr){} //default constructor by wenderyang

GrayImage::GrayImage(int width, int height, int **pixels) : Image(width, height), pixels(pixels) {} //common memory address

GrayImage::~GrayImage() {
    // Free the memory allocated for pixels
    if(this->pixels)
    {
        for(int i=0;i<this->height;i++)
        {
            delete [] pixels[i];
        }
        delete [] pixels;
    }
}

bool GrayImage::LoadImage(string filename) { //type by wenderyang
    int w, h;
    int **loaded_pixels = im.Load_Gray(filename, &w, &h); //Load gray image
    if (!loaded_pixels) { //判斷是否有引入到
        return false;
    }
    // Free existing pixels if they exist
    if (pixels) 
    {
        for (int i = 0; i < this->height; ++i) 
        {
            delete[] pixels[i];
        }
        delete[] pixels;
    }
    this->height = h;
    this->width = w;
    this->pixels = new int*[h];
    for(int i=0;i<h;i++)
    {
        pixels[i] = new int[w];
    }
    pixels = loaded_pixels;

    return true;
}

void GrayImage::DumpImage(string filename) {
    this->im.Dump_Gray(width, height, pixels, filename);
}

void GrayImage::Display_X_Server() {
    this->im.Display_Gray_X_Server(width, height, pixels);
}

void GrayImage::Display_ASCII() {
    this->im.Display_Gray_ASCII(width, height, pixels);
}

void GrayImage::Display_CMD() { //the function has no filename argument
    string temp_filename = "temp_image.jpg";  
    this->DumpImage(temp_filename);
    im.Display_Gray_CMD(temp_filename);
    string tmp = "rm" + temp_filename;
    system(tmp.c_str());
}


int GrayImage::get_pixel(int x, int y) const {
    if (x < 0 || x >= height || y < 0 || y >= width) { //判斷是否為有效圖
        //std::cerr << "Pixel coordinates out of bounds" << std::endl;
        return -1;
    }
    return pixels[x][y];
}

void GrayImage::set_pixels(int x, int y, int value) {
    if (x < 0 || x >= height || y < 0 || y >= width) {
        //std::cerr << "Pixel coordinates out of bounds" << std::endl;
    }
    pixels[x][y] = std::min(std::max(value, 0), 255); //讓圖在0< value <255 range.
}

int GrayImage::get_pixel(int x, int y, int c) const
{
    return pixels[x][y];
}

void GrayImage::set_pixel(int x, int y, int c, int value){}

void GrayImage::set_height(int h) {
    this->height = h;
}

void GrayImage::set_width(int w) {
    this->width = w;
}



void GrayImage::PreviousDelete() {
    for (int i = 0; i < this->height; ++i) {
        delete[] this->pixels[i];
    }
    delete[] this->pixels;
}

void GrayImage::SetPrivate(int w, int h, int*** pixel) {}

void GrayImage::Initial(int w,int h)
{
  this->width = w;
  this->height = h;
  this->pixels = new int*[h];
  for(int i=0;i<h;i++)
  {
    pixels[i] = new int[w];
  }
}
