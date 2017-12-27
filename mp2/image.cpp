#include "image.h"
#include "png.h"
#include<iostream>
using namespace std;

/**
 *this function flips the image about a vertical line through its center by swapping pixels.
 */
void Image::flipleft()
{
  //for the left part of the image, x will be changed while y will not be chaged
  for(size_t x=0; x<width()/2; x++)
  {
    for(size_t y=0; y<height(); y++)
    {
      //set a pointer (*this) as the pixel of the image that is doing the function
      //dereference (*this) and put the value of left-side part into temp
      RGBAPixel temp=*(*this)(x,y);
      //for 0<=x<=width()-1, put the value in the right-side into left-side
      *(*this)(x,y)=*(*this)(width()-1-x,y);
      //finally, put the original stored left-side value in temp into right-side of dereference of (*this)
      *(*this)(width()-1-x,y)=temp;
    }
  }
}


/**
 *this function adds to the red, green, and blue parts of each pixel in the image.
 *Overflow is prevented: if the result would be less than 0, it is 0.
 *If the result would be greater than 255, it is 255.
 */
void Image::adjustbrightness(int r, int g, int b)
{
  for (size_t y = 0; y < height(); y++)
  {
    for (size_t x = 0; x < width(); x++)
    {
    RGBAPixel* temp=(*this)(x,y);
///red color
      if(temp->red + r > 255)
         {
           temp->red = 255;
         }
      else if (temp->red + r < 0)
         {
            temp->red = 0;
         }
      else
        {
          temp->red = temp->red + r;
        }
///green color
      if(temp->green + g > 255)
           {
             temp->green = 255;
           }
      else if (temp->green + g < 0)
           {
              temp->green = 0;
           }
      else
          {
            temp->green = temp->green + g;
          }
///blue color
      if(temp->blue + b > 255)
           {
             temp->blue = 255;
           }
      else if (temp->blue + b < 0)
           {
              temp->blue = 0;
           }
      else
          {
            temp->blue = temp->blue + b;
          }
      }
  }

}


/**
 *Makes each RGB component of each pixel iequal to 255 minus its original value.
 *That is, the colors become the opposite of what they were, makeing a color-opposite of the original image.
 */
void Image::invertcolors()
{
  for (size_t x = 0; x < width(); x++)
  {
     for (size_t y = 0; y < height(); y++)
     {
        (*this)(x,y)->red =255-(*this)(x,y)->red;
        (*this)(x,y)->green =255-(*this)(x,y)->green;
        (*this)(x,y)->blue =255-(*this)(x,y)->blue;
     }
  }

}
