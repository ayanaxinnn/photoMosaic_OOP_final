#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"
#include <string>

class RGBImage : public Image {
private:
    int*** pixels;

public:
    RGBImage();
    RGBImage(int width, int height, int*** pixels);
    ~RGBImage();

    bool LoadImage(std::string filename);
    void DumpImage(std::string filename);
    void Display_X_Server();
    void Display_ASCII();
    void Display_CMD();

    void set_height(int h);
    void set_width(int w);
    void PreviousDelete();
    void SetPrivate(int w, int h, int*** pixel);
    int get_pixel(int x, int y, int c) const;
    void set_pixel(int x, int y, int c, int value);
    
    void initial(int w,int h);
};

#endif
