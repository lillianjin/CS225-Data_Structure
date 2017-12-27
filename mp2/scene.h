/**
 * @file scene.h
 * Definition of the Scene class.
 */
#ifndef SCENE_H
#define SCENE_H

#include<iostream>
#include "rgbapixel.h"
#include "image.h"
#include "png.h"
using namespace std;

class Scene
{
public:
  /**
   * Creates a default Scene image.
   * Initializes this Scene object to be able to hold "max" number of images with indices 0 through max-1.
   * assume that max > 0.
   */
  Scene(int a);

  /**
   * Frees all space that was dynamically allocated by this Scene.
   */
  ~Scene();

  /**
   *The copy constructor makes this Scene an independent copy of the source.
   *Create a copy() helper function and call it here.
   */
  Scene(const Scene & source);

  /**
   *The assignment operator for the Scene class.
   *checks for self assignment, (2) then deletes everything this Scene has allocated
   *then makes this Scene an independent copy of the source
   *then returns a reference to the current instance.
   */
  Scene const & operator=(const Scene & source);

  /**
   *Modifies the size of the array of Image pointers without changing their indices.
   *The new set of valid indices will be from 0 to (newmax - 1).
   * If this cannot be done because there are non-null pointers outside the range [0, newmax-1], use cout << "invalid newmax" << endl;
   * assume newmax is greater than zero.
   */
  void changemaxlayers(int newmax);

  /**
   *This function will add a picture to the scene, by placing it in the array cell corresponding to the given index, and storing its x coordinate and y coordinate.
   *If there is already an Image in cell location index it should be replaced by the new Image. If the index is not within the range [0, max-1], use cout << "index out of bounds" << endl;
   *assume that x and y are integers in the range [0, MAXINT].
   */
  void addpicture(const char* Filename, int index, int x, int y);

  /**
   *Moves an Image from one layer to another.
   *You are not allowed to dynamically allocate anything in this function. Rather, just move the pointer.
   *If the new index is the same as the old index, do nothing and return.
   *If the destination is already occupied, delete the image there. The source index should be marked vacant by making it value NULL.
   *If either index is invalid, do nothing and use cout << "invalid index" << endl;
   */
  void changelayer(int index, int newindex);

  /**
   *Changes the x and y coordinates of the Image in the specified layer.
   *If the index is invalid or if it contains a NULL pointer, do nothing and use cout << "invalid index" << endl;
   *assume that x and y are integers in the range [0, MAXINT].
   */
  void translate(int index, int xcoord, int ycoord);

  /**
   *Deletes the Image at the given index.
   *If the index is invalid or if it contains a NULL pointer, do nothing and cout << "invalid index" << endl;
   */
  void deletepicture(int index);

  /**
   *This function will return a pointer to the Image at the specified index, not a copy of it.
   *That way, the user can modify the Image. If the index is invalid, return NULL and print cout << "invalid index" << endl;
   */
  Image* getpicture(int index) const;

  /**
   *Draws the whole scene on one Image and returns that Image by value.
   *Images in the scene will be drawn in order from index 0 to index (max-1) at the stored coordinates. Do not use the alpha channel or any other transparency.
   *The x and y coordinates of an Image are the coordinates of its upper-left corner pixel in the output of this function.
   *Image drawscene() const;
   */
   Image drawscene() const;

 private:
   /**
    * Cctor/assignment operator copy helper function.
    */
   void clear();

   /**
    * Destructor/assignment operator clear helper function.
    */
   void copy(const Scene& source);

   int max;
   int* xcoords;
   int* ycoords;
   Image** maximage;

};
#endif
