#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "rgb_image.h"
#include "image.h"
#include"data_loader.h"
class PhotoMosaic {
private: 
    std::vector<Image*> smallImage;
    RGBImage BigImage;
    //int GCD;
    int kernalSize_h;
    int kernalSize_w;
public:
    PhotoMosaic();
    PhotoMosaic(const std::string targetImageFile);
    void InputsmallImage(const std::string smallImageFilename);
    //void GCDofBigImage();
    void NormalizesmallImage();
    int CalculateDifference(int h, int w);
    void resultMosaic(RGBImage& Final);
};

#endif
