#ifndef BIT_FIELD_FILTER_H
#define BIT_FIELD_FILTER_H

#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include <vector>
#include <iostream>

class BitFieldFilter { //對所有圖片都有相同的function(濾鏡)
public:
    static void ApplyBoxFilter(GrayImage &src, GrayImage &dst, int ksize);
    static void ApplyIdentifyFilter(GrayImage &src, GrayImage &dst);
    static void ApplyMedianFilter(GrayImage &src, GrayImage &dst, int ksize);
    static void ApplySharpeningFilter(GrayImage &src, GrayImage &dst);
    static void ApplyReverseFilter(GrayImage &src, GrayImage &dst); // 修改為接受源圖片
    static void ApplyEnhanceContrast(GrayImage &src, GrayImage &dst, double a, double b); // 修改為接受源圖片
    static void ApplyChangeBrightness(GrayImage &src, GrayImage &dst, double c); // 修改為接受源圖片
    static void ApplySobelGradientFilter(GrayImage &src, GrayImage &dst);
    static void ApplyReflectionFilter(GrayImage &src, GrayImage &dst, char direct);
    static void ApplyRemoveBlueLightFilter(RGBImage &src, RGBImage &dst);

private:
    static void zeroPadArray(const std::vector<std::vector<int>>& original, std::vector<std::vector<int>>& padded, int filsize); 
    //在原有矩陣外加上一排 0
};

#endif // BIT_FIELD_FILTER_H
