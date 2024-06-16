#include <iostream>
#include <string>
#include <vector>
#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"
#include "data_loader.h"
#define ENABLE_X_SERVER true

void line() {
    for (int i = 0; i < 115; i++) std::cout << "-";
    std::cout << std::endl;
}

char choose() {
    std::cout << "Let's choose the filter!\n";
    std::cout << "tap '1' to choose Box filter\n";
    std::cout << "tap '2' to choose Identify filter\n";
    std::cout << "tap '3' to choose Median filter\n";
    std::cout << "tap '4' to choose Sharpening Filter\n";
    std::cout << "tap '5' to choose Reverse Filter\n";
    std::cout << "tap '6' to choose Enhance contrast\n";
    std::cout << "tap '7' to choose change brightness\n";
    std::cout << "tap '8' to choose Sobel Gradient filter\n";
    std::cout << "tap '9' to choose Reflection filter\n";
    std::cout << "tap 'a' to choose Removing Blue Light filter\n";
    std::cout << "Type in a number to choose a filter: ";
    char ch;
    std::cin >> ch;
    return ch;
}

void zeroPadArray(const std::vector<std::vector<int>>& original, std::vector<std::vector<int>>& padded, int filsize) {
    int padding = filsize / 2;
    int rows = original.size();
    int cols = original[0].size();
    padded.resize(rows + 2 * padding, std::vector<int>(cols + 2 * padding, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            padded[i + padding][j + padding] = original[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    Image *img1 = new GrayImage();
    if (img1->LoadImage("Image-Folder/mnist/img_100.jpg")) {
        img1->DumpImage("img1.jpg");
        if(ENABLE_X_SERVER){
          img1->Display_X_Server();
        }
        
        img1->Display_CMD();
    } else {
        std::cerr << "Failed to load img_100.jpg" << std::endl;
    }

    Image *img2 = new RGBImage();
    if (img2->LoadImage("Image-Folder/lena.jpg")) {
        img2->DumpImage("img2.jpg");
        if(ENABLE_X_SERVER){
          img2->Display_X_Server();
        }
        img2->Display_CMD();
    } else {
        std::cerr << "Failed to load lena.jpg" << std::endl;
    }

    line();
    
    std::cout << "Hello ^^" << std::endl;
    std::cout << "bit_field......for gray image!!!" << std::endl;
    std::cout<<"we default ania.jpg  to use\n";
    bool startBitField = true;
    while (startBitField) {
    /*
        std::cout << "Please type in your image's path to start the filter program: ";
        
        std::cin >> path;
        
        if (!img3.LoadImage(path)) {
            std::cerr << "Failed to load image from path: " << path << std::endl;
            continue;
        }
        */
        line();
        
        GrayImage img3;
        std::string path = "Image-Folder/ania.jpg";
        img3.LoadImage(path);
        
        RGBImage img5;
        std::string pathRGB = "Image-Folder/4k_owl.jpg";
        img5.LoadImage(pathRGB);
        
        GrayImage output_images[4];
        
        RGBImage output_RGBimage;
        
        char filter_choice = choose();
        
        BitFieldFilter bit;

        switch (filter_choice) {
            case '1': {
                line();
                std::cout << "you choose the BOX FILTER!!!!!!!\n";
                int filter_sizes[4];
                for (int i = 0; i < 4; i++) {
                    std::cout << "Give whatever filter size you want, the size number should be odd: ";
                    std::cin >> filter_sizes[i];
                    while (filter_sizes[i] % 2 == 0) {
                        std::cout << "WTF!!!! it is even!!! please re-enter the filter size: ";
                        std::cin >> filter_sizes[i];
                    }
                }
                for (int i = 0; i < 4; i++) {
                    std::cout << filter_sizes[i] << "x" << filter_sizes[i] << " box filter has been confirmed!!!!" << std::endl;
                    bit.ApplyBoxFilter(img3, output_images[i], filter_sizes[i]);
                    std::cout << filter_sizes[i] << "x" << filter_sizes[i] << " box filter has been applied to your image, please check it ^_^" << std::endl;
                    if(ENABLE_X_SERVER){
                      output_images[i].Display_X_Server();
                    }
                    //output_images[i].Display_X_Server();
                    output_images[i].Display_CMD();
                }
                line();
                break;
            }

            case '2': {
                line();
                std::cout << "you choose the IDENTIFY FILTER!!!!!!!\n";
                bit.ApplyIdentifyFilter(img3, output_images[0]);
                std::cout << "Identify filter has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server();
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }

            case '3': {
                line();
                std::cout << "you choose the MEDIAN FILTER!!!!!!!\n";
                int filter_size;
                std::cout << "Give whatever filter size you want, the size number should be odd: ";
                std::cin >> filter_size;
                while (filter_size % 2 == 0) {
                    std::cout << "WTF!!!! it is even!!! please re-enter the filter size: ";
                    std::cin >> filter_size;
                }
                std::cout << filter_size << "x" << filter_size << " median filter has been confirmed!" << std::endl;
                bit.ApplyMedianFilter(img3, output_images[0], filter_size);
                std::cout << filter_size << "x" << filter_size << " median filter has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server();
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }

            case '4': {
                line();
                std::cout << "you choose the SHARPENING FILTER!!!!!!!\n";
                bit.ApplySharpeningFilter(img3, output_images[0]);
                std::cout << "Sharpening filter has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server();
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }

            case '5': {
                line();
                std::cout << "you choose the REVERSE FILTER!!!!!!!\n";
                bit.ApplyReverseFilter(img3,output_images[0]);
                std::cout << "Reverse filter has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server();
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }

            case '6': {
                line();
                std::cout << "you choose the ENHANCE CONTRAST!!!!!!!\n";
                double a, b;
                std::cout << "For the function f(x) = a*x + b, give two constants 'a' and 'b' determined by you." << std::endl;
                std::cout << "Suggested value is a = 1.2 and b = -60, or you can try other values by yourself." << std::endl;
                std::cout << "Type in a: ";
                std::cin >> a;
                std::cout << "Type in b: ";
                std::cin >> b;
                bit.ApplyEnhanceContrast(img3,output_images[0], a, b);
                std::cout << "Enhance contrast has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server();
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }

            case '7': {
                std::cout << "you choose the CHANGE BRIGHTNESS!!!!!!!\n";
                double c;
                std::cout << "For the function f(x) = c*ln(1 + x), give a constant 'c' determined by you." << std::endl;
                std::cout << "brighten: c > 26, darken: c < 26" << std::endl;
                std::cout << "Suggested value is c = 10, 20, 45.985, or you can try other values by yourself." << std::endl;
                std::cout << "Type in c: ";
                std::cin >> c;
                bit.ApplyChangeBrightness(img3,output_images[0], c);
                std::cout << "Change brightness has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server();
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }

            case '8': {
                std::cout << "you choose the SOBEL GRADIENT FILTER!!!!!!!\n";
                bit.ApplySobelGradientFilter(img3, output_images[0]);
                std::cout << "Sobel Gradient filter has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server(); 
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }
            
            case '9': {
                std::cout << "you choose the REFLECTION FILTER!!!!!!!\n";
                char command;
                std::cout << "Please enter V or H to choose vertical/horiontial reflection: ";
                cin >> command;
                bit.ApplyReflectionFilter(img3, output_images[0],command);
                std::cout << "Reflection filter has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_images[0].Display_X_Server(); 
                    }
                output_images[0].Display_CMD();
                line();
                break;
            }
            
            case 'a': {
                std::cout << "you choose the REMOVING BLUE LIGHT FILTER!!!!!!!\n";
                bit.ApplyReflectionFilter(img5, output_RGBimage);
                std::cout << "Removing blue light filter has been applied to your image, please check it ^_^" << std::endl;
                if(ENABLE_X_SERVER){
                      output_RGBimage.Display_X_Server(); 
                    }
                output_RGBimage.Display_CMD();
                line();
                break;
            }

            default: {
                std::cout << "Invalid option. Please choose a valid filter." << std::endl;
                break;
            }
        }

        std::cout << "Wanna play again? (Y/N): ";
        char playAgain;
        std::cin >> playAgain;
        if (playAgain == 'N' || playAgain == 'n') {
            startBitField = false;
        }
        
        line();
        line();
    }

        
        
    std::cout << "Now...it's time to check photo mosaic!!!!\n";
    std::cout << "We default the path to cat\n";

    std::string path3 = "Image-Folder/girl_2x.png";
    PhotoMosaic photo(path3);
    
    std::string path2;
    for (int j = 1; j <100; j++) {
        if (j < 10) {
            path2 = "Image-Folder/cifar10/cat_000" + std::to_string(j) + ".png";
            photo.InputsmallImage(path2);
        }else if (j < 100) {
            path2 = "Image-Folder/cifar10/cat_00" + std::to_string(j) + ".png";
            photo.InputsmallImage(path2);
        }
    }
    
    photo.NormalizesmallImage();
    RGBImage img4;
    photo.resultMosaic(img4);
    if (ENABLE_X_SERVER) {
        img4.Display_X_Server();
    }
    img4.Display_CMD();

    return 0;

}

