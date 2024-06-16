#include "photo_mosaic.h"

#include <string>
#include <limits>
#include <cmath>

using namespace std;

PhotoMosaic::PhotoMosaic(): kernalSize_h(32), kernalSize_w(32){}

PhotoMosaic::PhotoMosaic(const std::string targetImageFilename) {
    BigImage.LoadImage(targetImageFilename);
    //this->GCDofBigImage();
    this->kernalSize_h = 32;
    this->kernalSize_w = 32;
}

void PhotoMosaic::InputsmallImage(const std::string smallImageFilename) {
    int w, h;
    Data_Loader temp;
    int*** pixel = temp.Load_RGB(smallImageFilename, &w, &h);
    smallImage.push_back(new RGBImage{w, h, pixel});
}
/*
void PhotoMosaic::GCDofBigImage() {
    int a = BigImage.get_height();
    int b = BigImage.get_width();
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    this->GCD = a;
}
*/
void PhotoMosaic::NormalizesmallImage() {
    int h = this->kernalSize_h;
    int w = this->kernalSize_w;
    for(std::vector<Image*>::size_type t = 0; t < smallImage.size(); t++) {
        if(smallImage[t]->get_height() > h && smallImage[t]->get_width() > w) {
            int*** pixel = new int**[h];
            for(int i = 0; i < h; i++) {
                pixel[i] = new int*[w];
                for(int j = 0; j < w; j++) {
                    pixel[i][j] = new int[3];
                }
            }
            for(int i = 0; i < h; i++) {
                for(int j = 0; j < w; j++) {
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = smallImage[t]->get_pixel(i, j, z);
                    }
                }
            }
            smallImage[t]->PreviousDelete();
            smallImage[t]->SetPrivate(w, h, pixel);
            continue;
        }
        else if(smallImage[t]->get_height() < h && smallImage[t]->get_width() < w) {
            int*** pixel = new int**[h];
            for(int i = 0; i < h; i++) {
                pixel[i] = new int*[w];
                for(int j = 0; j < w; j++) {
                    pixel[i][j] = new int[3];
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = 255; // Initialize with white
                    }
                }
            }
            for(int i = 0; i < smallImage[t]->get_height(); i++) {
                for(int j = 0; j < smallImage[t]->get_width(); j++) {
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = smallImage[t]->get_pixel(i, j, z);
                    }
                }
            }
            smallImage[t]->PreviousDelete();
            smallImage[t]->SetPrivate(w, h, pixel);
            continue;
        }
        if(smallImage[t]->get_height() > h) {
            int*** pixel = new int**[h];
            for(int i = 0; i < h; i++) {
                pixel[i] = new int*[smallImage[t]->get_width()];
                for(int j = 0; j < smallImage[t]->get_width(); j++) {
                    pixel[i][j] = new int[3];
                }
            }
            for(int i = 0; i < h; i++) {
                for(int j = 0; j < smallImage[t]->get_width(); j++) {
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = smallImage[t]->get_pixel(i, j, z);
                    }
                }
            }
            smallImage[t]->PreviousDelete();
            smallImage[t]->SetPrivate(smallImage[t]->get_width(), h, pixel);
        } else if(smallImage[t]->get_height() < h) {
            int*** pixel = new int**[h];
            for(int i = 0; i < h; i++) {
                pixel[i] = new int*[smallImage[t]->get_width()];
                for(int j = 0; j < smallImage[t]->get_width(); j++) {
                    pixel[i][j] = new int[3];
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = 255; // Initialize with white
                    }
                }
            }
            for(int i = 0; i < smallImage[t]->get_height(); i++) {
                for(int j = 0; j < smallImage[t]->get_width(); j++) {
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = smallImage[t]->get_pixel(i, j, z);
                    }
                }
            }
            smallImage[t]->PreviousDelete();
            smallImage[t]->SetPrivate(smallImage[t]->get_width(), h, pixel);
        }
        if(smallImage[t]->get_width() > w) {
            int*** pixel = new int**[smallImage[t]->get_height()];
            for(int i = 0; i < smallImage[t]->get_height(); i++) {
                pixel[i] = new int*[w];
                for(int j = 0; j < w; j++) {
                    pixel[i][j] = new int[3];
                }
            }
            for(int i = 0; i < smallImage[t]->get_height(); i++) {
                for(int j = 0; j < w; j++) {
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = smallImage[t]->get_pixel(i, j, z);
                    }
                }
            }
            smallImage[t]->PreviousDelete();
            smallImage[t]->SetPrivate(w, smallImage[t]->get_height(), pixel);
        } else if(smallImage[t]->get_width() < w) {
            int*** pixel = new int**[smallImage[t]->get_height()];
            for(int i = 0; i < h; i++) {
                pixel[i] = new int*[w];
                for(int j = 0; j < w; j++) {
                    pixel[i][j] = new int[3];
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = 255; // Initialize with white
                    }
                }
            }
            for(int i = 0; i < smallImage[t]->get_height(); i++) {
                for(int j = 0; j < smallImage[t]->get_width(); j++) {
                    for(int z = 0; z < 3; z++) {
                        pixel[i][j][z] = smallImage[t]->get_pixel(i, j, z);
                    }
                }
            }
            smallImage[t]->PreviousDelete();
            smallImage[t]->SetPrivate(w, smallImage[t]->get_height(), pixel);
        }
    }
}

int PhotoMosaic::CalculateDifference(int h, int w) {
    int sumR = 0;
    int sumG = 0;
    int sumB = 0;
    double Big_R_Average;
    double Big_G_Average;
    double Big_B_Average;
    int Area = this->kernalSize_h * this->kernalSize_w;
    for(int i = h; i < h + this->kernalSize_h; i++) {
        for(int j = w; j < w + this->kernalSize_w; j++) {
            sumR += BigImage.get_pixel(i, j, 0);
            sumG += BigImage.get_pixel(i, j, 1);
            sumB += BigImage.get_pixel(i, j, 2);
        }
    }
    Big_R_Average = static_cast<double>(sumR) / Area;
    Big_G_Average = static_cast<double>(sumG) / Area;
    Big_B_Average = static_cast<double>(sumB) / Area;

    vector<double> diff(smallImage.size());
    double min = 100000;
    for(std::vector<Image*>::size_type t = 0; t < smallImage.size(); t++) {
        int SsumR = 0;
        int SsumG = 0;
        int SsumB = 0;
        double S_R_Average;
        double S_G_Average;
        double S_B_Average;
        for(int i = 0; i < this->kernalSize_h; i++) {
            for(int j = 0; j < this->kernalSize_w; j++) {
                SsumR += smallImage[t]->get_pixel(i, j, 0);
                SsumG += smallImage[t]->get_pixel(i, j, 1);
                SsumB += smallImage[t]->get_pixel(i, j, 2);
            }
        }
        S_R_Average = static_cast<double>(SsumR) / Area;
        S_G_Average = static_cast<double>(SsumG) / Area;
        S_B_Average = static_cast<double>(SsumB) / Area;

        diff[t] = sqrt(pow(S_R_Average - Big_R_Average, 2) + pow(S_G_Average - Big_G_Average, 2) + pow(S_B_Average - Big_B_Average, 2));
        if(diff[t] < min) {
            min = diff[t];
        }
    }
    for(std::vector<Image*>::size_type i = 0; i < smallImage.size(); i++) {
        if(min == diff[i]) {
            return i;
            break;
        }
    }
    return -1; // Added to handle the case where no matching image is found
}

void PhotoMosaic::resultMosaic(RGBImage& Final) {
    vector<int> ImageRemark;
    for (int i = 0; i < BigImage.get_height(); i += this->kernalSize_h) {
        for (int j = 0; j < BigImage.get_width(); j += this->kernalSize_w) {
            ImageRemark.push_back(this->CalculateDifference(i, j));
        }
    }

    int*** pixel = new int**[BigImage.get_height()];
    for (int i = 0; i < BigImage.get_height(); i++) {
        pixel[i] = new int*[BigImage.get_width()];
        for (int j = 0; j < BigImage.get_width(); j++) {
            pixel[i][j] = new int[3];
        }
    }

    Final.SetPrivate(BigImage.get_width(), BigImage.get_height(), pixel);

    int index = 0;
    for (int i = 0; i < BigImage.get_height(); i += this->kernalSize_h) {
        for (int j = 0; j < BigImage.get_width(); j += this->kernalSize_w) {
            int smallImageIndex = ImageRemark[index];
            for (int x = i; x < i + this->kernalSize_h; x++) {
                for (int y = j; y < j + this->kernalSize_w; y++) {
                    Final.set_pixel(x, y, 0, smallImage[smallImageIndex]->get_pixel(x - i, y - j, 0));
                    Final.set_pixel(x, y, 1, smallImage[smallImageIndex]->get_pixel(x - i, y - j, 1));
                    Final.set_pixel(x, y, 2, smallImage[smallImageIndex]->get_pixel(x - i, y - j, 2));
                }
            }
            index++;
        }
    }
}
