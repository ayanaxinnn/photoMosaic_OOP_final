#include "bit_field_filter.h"

void BitFieldFilter::zeroPadArray(const std::vector<std::vector<int>>& original, std::vector<std::vector<int>>& padded, int filsize/*過濾器的大小*/) /*零填充*/{
    
    int padSize = filsize / 2;//上下左右填充的大小
    int originalRows = original.size(); //行數
    int originalCols = original[0].size(); //列數
    int paddedRows = originalRows + 2 * padSize; //填充後的行數
    int paddedCols = originalCols + 2 * padSize; //填充後的列數

    padded.assign(paddedRows, std::vector<int>(paddedCols, 0)); //將填充過後的array初始化元素為零
    for (int i = 0; i < originalRows; i++) {
        for (int j = 0; j < originalCols; j++) {
            padded[i + padSize][j + padSize] = original[i][j]; //讓中間block之外的元素為零
        }
    }
}

void BitFieldFilter::ApplyBoxFilter(GrayImage &src, GrayImage &dst, int ksize/*濾波器大小*/) { //使用盒濾波器
    int rows = src.get_height(); //讀取圖像的高度
    int cols = src.get_width(); //寬度
    std::vector<std::vector<int>> padded(rows+2*(ksize/2), std::vector<int>(cols+2*(ksize/2))); //定義填充矩陣
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols)); //初始化原始矩陣(將image數據複製過去濾波器)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j); //copy step
        }
    }
    zeroPadArray(original, padded, ksize); //零填充

    dst.Initial(cols,rows);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sum = 0;
            for (int ki = -ksize / 2; ki <= ksize / 2; ki++) {
                for (int kj = -ksize / 2; kj <= ksize / 2; kj++) {
                    sum += padded[i + ki + ksize / 2][j + kj + ksize / 2]; //讓ksize X ksize block內的數值取sum後除上 ksize * ksize
                }
            }
            dst.set_pixels(i, j, sum / (ksize * ksize)); //將數值弄到origin matrix
        }
    }
}

void BitFieldFilter::ApplyIdentifyFilter(GrayImage &src, GrayImage &dst) { //對灰度的辨識濾波器
    int rows = src.get_height();
    int cols = src.get_width();
    std::vector<std::vector<int>> padded; // 定義填充矩陣
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols));//初始化原始矩陣(將image數據複製過去濾波器)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j); //copy data
        }
    }
    zeroPadArray(original, padded, 3); //辨識濾波器 size 為3
    
    dst.Initial(cols,rows);

    int filter[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}; // ERROR 有說法說這理應該為identity matrix I3 //{(0,0,0),(0,1,0),(0,0,0)}
    for (int i = 1; i < rows + 1; i++) {
        for (int j = 1; j < cols + 1; j++) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ki++) {
                for (int kj = -1; kj <= 1; kj++) {
                    sum += padded[i + ki][j + kj] * filter[ki + 1][kj + 1]; //將目標entry附近3 X 3矩陣乘上 identity matrix 定義成新的entry
                }
            }
            dst.set_pixels(i - 1, j - 1, sum); //將圖片回傳回去新灰階圖
        }
    }
}

void BitFieldFilter::ApplyMedianFilter(GrayImage &src, GrayImage &dst, int ksize) { //中值濾波器
    int rows = src.get_height();
    int cols = src.get_width();
    std::vector<std::vector<int>> padded; //定義填充矩陣
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols)); //初始化origin matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j); //將image data複製過去
        }
    }
    zeroPadArray(original, padded, ksize); //填充
    
    dst.Initial(cols,rows);

    std::vector<int> filter(ksize * ksize); //初始vector有ksize*ksize的空間
    int padsize = ksize / 2;
    for (int i = padsize; i < rows + padsize; i++) {
        for (int j = padsize; j < cols + padsize; j++) {
            int index = 0;
            for (int ki = -padsize; ki <= padsize; ki++) {
                for (int kj = -padsize; kj <= padsize; kj++) {
                    filter[index++] = padded[i + ki][j + kj];
                }
            }
            std::sort(filter.begin(), filter.end());
            dst.set_pixels(i - padsize, j - padsize, filter[ksize * ksize / 2]); //取中間值
        }
    }
}

void BitFieldFilter::ApplySharpeningFilter(GrayImage &src, GrayImage &dst) {
    int rows = src.get_height();
    int cols = src.get_width();
    std::vector<std::vector<int>> padded;
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j);//將image data複製過去
        }
    }
    zeroPadArray(original, padded, 3);
    
    dst.Initial(cols,rows);

    int filter[3][3] = {{1, 1, 1}, {1, -6, 1}, {1, 1, 1}}; //定義銳化濾波器與大小
    int padsize = 1;
    for (int i = padsize; i < rows + padsize; i++) {
        for (int j = padsize; j < cols + padsize; j++) {
            int sum = 0;
            for (int ki = -padsize; ki <= padsize; ki++) {
                for (int kj = -padsize; kj <= padsize; kj++) {
                    sum += padded[i + ki][j + kj] * filter[ki + padsize][kj + padsize]; //銳化處理
                }
            }
            dst.set_pixels(i - padsize, j - padsize, std::min(std::max(sum, 0), 255)); //確保值都在0~255之間
        }
    }
}

void BitFieldFilter::ApplyReverseFilter(GrayImage &src, GrayImage &dst) {
    int rows = src.get_height();
    int cols = src.get_width();
    std::vector<std::vector<int>> padded;
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j);//將image data複製過去
        }
    }
    
    zeroPadArray(original, padded,0);
    
    dst.Initial(cols,rows);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dst.set_pixels(i, j, 255 - src.get_pixel(i, j)); //灰度影像反轉
        }
    }
}

void BitFieldFilter::ApplyEnhanceContrast(GrayImage &src, GrayImage &dst, double a, double b) { //增強對比度->a、b是參數
    int rows = src.get_height();
    int cols = src.get_width();
    std::vector<std::vector<int>> padded;
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j);//將image data複製過去
        }
    }
    
    zeroPadArray(original, padded,0);
    
    dst.Initial(cols,rows);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int newVal = static_cast<int>(round(a * src.get_pixel(i, j) + b)); //線性增強 ax+b ， x為像素 //round為浮點數取四捨五入
            dst.set_pixels(i, j, std::min(std::max(newVal, 0), 255));
        }
    }
}

void BitFieldFilter::ApplyChangeBrightness(GrayImage &src, GrayImage &dst, double c) { //調整亮度，c為參數
    int rows = src.get_height();
    int cols = src.get_width();
    
    std::vector<std::vector<int>> padded;
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j);//將image data複製過去
        }
    }
    
    zeroPadArray(original, padded,0);
    
    dst.Initial(cols,rows);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int newVal = static_cast<int>(round(c * log(1 + src.get_pixel(i, j)))); //放大c *log(1+像素)倍，然後再取四捨五入
            dst.set_pixels(i, j, std::min(std::max(newVal, 0), 255));//確保值都在0~255之間
        }
    }
}
void BitFieldFilter::ApplySobelGradientFilter(GrayImage &src, GrayImage &dst) {
    int rows = src.get_height();
    int cols = src.get_width();
    std::vector<std::vector<int>> padded;
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j);//將image數值輸入
        }
    }
    zeroPadArray(original, padded, 3);

    dst.Initial(cols,rows);
    
    int filter_h[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};//定義水平Sobel濾波器
    int filter_v[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};//定義垂直Sobel濾波器
    int padsize = 1;
    for (int i = padsize; i < rows + padsize; i++) {
        for (int j = padsize; j < cols + padsize; j++) {
            int grad_x = 0, grad_y = 0;
            for (int ki = -padsize; ki <= padsize; ki++) {
                for (int kj = -padsize; kj <= padsize; kj++) {
                    grad_x += padded[i + ki][j + kj] * filter_h[ki + padsize][kj + padsize];
                    grad_y += padded[i + ki][j + kj] * filter_v[ki + padsize][kj + padsize];
                }
            }
            int gradient = static_cast<int>(round(sqrt(pow(grad_x, 2) + pow(grad_y, 2)))); //梯度幅度的運算
            dst.set_pixels(i - padsize, j - padsize, std::min(std::max(gradient, 0), 255));
        }
    }
}

void BitFieldFilter::ApplyReflectionFilter(GrayImage &src, GrayImage &dst, char direct)
{
    int rows = src.get_height();
    int cols = src.get_width();
    std::vector<std::vector<int>> padded;
    std::vector<std::vector<int>> original(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            original[i][j] = src.get_pixel(i, j);//將image數值輸入
        }
    }
    
    dst.Initial(cols,rows);
    
    if(direct == 'V')
    {
      for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
              dst.set_pixels(rows-i-1,j,original[i][j]);
          }
      }
    }else if(direct == 'H')
    {
      for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
              dst.set_pixels(i,cols-j-1,original[i][j]);
          }
      }
    }
  
}

void BitFieldFilter::ApplyRemoveBlueLightFilter(RGBImage &src, RGBImage &dst)
{
    int h,w;
    h = src.get_height();
    w = src.get_width();
    dst.initial(w,h);
    
    for(int i=0;i<h;i++)
    {
      for(int j=0;j<w;j++)
      {
        for(int z=0;z<3;z++)
        {
          if(z<2)
          {
            dst.set_pixel(i, j, z, src.get_pixel(i, j, z));
          }else
          {
            dst.set_pixel(i, j, z,0);
          }
        }
      }
    }
}

