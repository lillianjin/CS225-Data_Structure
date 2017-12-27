/**
 * @file main.cpp
 * this program uses the functions from the EasyPNG library to open a bitmap image named in.png, rotate the image by 180 degrees, and write the resulting image to the file out.png.
 */

#include <iostream>

#include "rgbapixel.h"
#include "png.h"

using namespace std;

/**
 *this function rotate the PNG image named in.png and return the result to another PNG image named out.png
 *the width and height of the two images are of the same
 *for each pixel in the image, rotate each one at one time
 */

int main()
{
  //set up the input and output image
  PNG* in=new PNG;


  //read the original size of the image "in.png"
  in->readFromFile("in.png");
  int height = in->height();
  int width = in->width();
  PNG* out=new PNG(width,height);

  //rotate each pixel at a time
  //the center of rotation is ((width-1)/2,(height-1)/2)
  //(x+x')/2=(width-1)/2
  //(y+y')/2=(height-1)/2
  for (int y = 0; y < height; y++)
  {
      for (int x = 0; x < width; x++)
      {
         (*out)(-x+width-1,-y+height-1)->red =(*in)(x,y)->red;
	       (*out)(-x+width-1,-y+height-1)->green = (*in)(x,y)->green;
	       (*out)(-x+width-1,-y+height-1)->blue = (*in)(x,y)->blue;
	       (*out)(-x+width-1,-y+height-1)->alpha = (*in)(x,y)->alpha;
       }
   }

  //save the output file
   out->writeToFile("out.png");
   return 0;
}
