#include "rgb_image.h"
#include <iostream>
#include <algorithm>

RGBImage::RGBImage() : Image(0, 0), pixels(nullptr) {}

RGBImage::RGBImage(int width, int height, int*** pixels) : Image(width, height), pixels(pixels) {}

RGBImage::~RGBImage() {
    if (pixels) {
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                delete[] pixels[i][j];
            }
            delete[] pixels[i];
        }
        delete[] pixels;
    }
}

bool RGBImage::LoadImage(std::string filename) {
    int w, h;
    int*** loaded_pixels = im.Load_RGB(filename, &w, &h);
    if (!loaded_pixels) {
        return false;
    }

    if (pixels) {
        for (int i = 0; i < this->height; ++i) {
            for (int j = 0; j < this->width; ++j) {
                delete[] pixels[i][j];
            }
            delete[] pixels[i];
        }
        delete[] pixels;
    }

    this->height = h;
    this->width = w;
    this->pixels = loaded_pixels;

    return true;
}

void RGBImage::DumpImage(std::string filename) {
    im.Dump_RGB(this->width, this->height, this->pixels, filename);
}

void RGBImage::Display_X_Server() {
    im.Display_RGB_X_Server(this->width, this->height, this->pixels);
}

void RGBImage::Display_ASCII() {
    im.Display_RGB_ASCII(this->width, this->height, this->pixels);
}

void RGBImage::Display_CMD() {
    std::string temp_filename = "temp_image.png";
    this->DumpImage(temp_filename);
    im.Display_RGB_CMD(temp_filename);
}

int RGBImage::get_pixel(int x, int y, int c) const {
    if (x < 0 || x >= height || y < 0 || y >= width || c < 0 || c >= 3) {
        //std::cerr << "Pixel coordinates or channel out of bounds" << std::endl;
        return -1;
    }
    return pixels[x][y][c];
}

void RGBImage::set_pixel(int x, int y, int c, int value) {
    if (x < 0 || x >= height || y < 0 || y >= width || c < 0 || c >= 3) {
        //std::cerr << "Pixel coordinates or channel out of bounds" << std::endl;
        return;
    }
    pixels[x][y][c] = std::min(std::max(value, 0), 255);
}

void RGBImage::set_height(int h) {
    this->height = h;
}

void RGBImage::set_width(int w) {
    this->width = w;
}

void RGBImage::PreviousDelete() {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            delete[] this->pixels[i][j];
        }
        delete[] this->pixels[i];
    }
    delete[] this->pixels;
}

void RGBImage::SetPrivate(int w, int h, int*** pixel) {
    this->width = w;
    this->height = h;
    this->pixels = new int**[h];
    for (int i = 0; i < h; i++) {
        this->pixels[i] = new int*[w];
        for (int j = 0; j < w; j++) {
            this->pixels[i][j] = new int[3];
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            for (int z = 0; z < 3; z++) {
                this->pixels[i][j][z] = pixel[i][j][z];
            }
        }
    }
}

void RGBImage::initial(int w,int h)
{
  this->height = h;
  tihs->width = w;
  this->pixels = new int**[h];
  for(int i=0;i<h;i++)
  {
    pixels[i] = new int*[w];
    for(int j=0;j<w;j++)
    {
      pixels[i][j] = new int[3];
    }
  }
}
