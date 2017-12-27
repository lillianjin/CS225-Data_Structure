#ifndef IMAGE_H
#define IMAGE_H

#include<iostream>
#include "rgbapixel.h"
#include "png.h"
#include "image.h"
using namespace std;

class Image : public PNG
{
public:
  void flipleft();
  void adjustbrightness(int r, int g, int b);
  void invertcolors();

};
#endif
