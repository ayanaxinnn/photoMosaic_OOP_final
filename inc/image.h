#ifndef _IMAGE_H_
#define _IMAGE_H_
#include"data_loader.h"
#include<string>
using namespace std;

class Image{
protected:
	int width;
	int height;
	static Data_Loader im; //讓gray image和RGB image有共同的data_loader
public:
	Image(int _width, int _height);
	~Image();
	virtual bool LoadImage(string filename) = 0; //為polymorphism鋪陳
	virtual void DumpImage(string filename) = 0;
	virtual void Display_X_Server() = 0;
	virtual void Display_ASCII() = 0;
	virtual void Display_CMD() = 0;
	virtual void set_height(int h) = 0;
	virtual void set_width(int w) = 0;
	virtual void PreviousDelete() = 0;
	virtual void SetPrivate(int w,int h,int*** pixel) = 0;
	virtual int get_pixel(int x, int y, int c) const = 0;
	virtual void set_pixel(int x, int y, int c, int value) = 0;
	
	int get_width();
	int get_height();
};

#endif
