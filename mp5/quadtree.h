/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */
 #ifndef QUADTREE_H
 #define QUADTREE_H
 #include <iostream>
 #include "png.h"

 class Quadtree
 {
 	public:
 	/**
 	 *no parameter constructor
 	 *produces an empty Quadtree object
 	 *i.e. one which has no associated QuadtreeNode objects, and in which root is NULL.
 	 */
 	Quadtree();


 	/**
 	 * build a Quadtree representing the upper-left d by d block of the source image
 	 * assume that d is a power of two, and width and height of source are each at least d
 	 * @source	 The source image to base this Quadtree on
 	 * @resolution	 The width and height of the sides of the image to be represented
 	 */
 	Quadtree(PNG const & source, int resolution);


 	/**
 	 * copy constructor
 	 */
 	Quadtree(Quadtree const & other);


 	/**
 	 * destructor
 	 */
 	~Quadtree();


 	/**
 	 * assignment operator
 	 * frees memory associated with this Quadtree
 	 * and sets its contents to be equal to the parameter's
 	 * Returns  A constant reference to the Quadtree value that was copied
 	 */
 	Quadtree const & operator=(Quadtree const & other);


 	/**
 	 * Deletes the current contents of this Quadtree object
 	 * turns it into a Quadtree object representing the upper-left d by d block of source
 	 * @source	 The source image to base this Quadtree on
 	 * @resolution	 The width and height of the sides of the image to be represented
 	 */
 	void buildTree(PNG const & source, int resolution);


 	/**
 	 * Gets the RGBAPixel corresponding to the pixel at coordinates (x, y) in the bitmap image which the Quadtree represents.
 	 * The pixel at the given (x, y) location is returned
 	 */
 	RGBAPixel getPixel(int x, int y) const;



 	/**
 	 * Returns the underlying PNG object represented by the Quadtree.
 	 * If the current Quadtree is empty (i.e., it was created by the default constructor)
 	 * then the returned PNG should be the one which is created by the default PNG constructor.
 	 */
 	PNG decompress() const;



 	/**
 	 * Rotates the Quadtree object's underlying image clockwise by 90 degrees.
 	 */
 	void clockwiseRotate();

 	/**
 	 * Compresses the image this Quadtree represents
   * @tolerance	The integer tolerance between two nodes that determines whether the subtree can be pruned
 	 */
 	void prune(int tolerance);


 	/**
 	 * This function is similar to prune; however, it does not actually prune the Quadtree.
   * it returns a count of the total number of leaves the Quadtree would have if it were pruned
 	 */
 	int pruneSize(int tolerance) const;


 	/**
 	 * Calculates and returns the minimum tolerance necessary to guarantee that upon pruning the tree
   * no more than numLeaves leaves remain in the Quadtree.
 	 */
 	int idealPrune( int numLeaves) const;


 	private:

    //QuadtreeNode builder(
   	// A simple class representing a single node of a Quadtree.
   	// You may want to add to this class; in particular, it could probably
   	// use a constructor or two...
   	class QuadtreeNode
   	{
   		public:
   		QuadtreeNode* nwChild;  // pointer to northwest child
   		QuadtreeNode* neChild;  // pointer to northeast child
   		QuadtreeNode* swChild;  // pointer to southwest child
   		QuadtreeNode* seChild;  // pointer to southeast child

   		RGBAPixel element;  // the pixel stored as this node's "data"
      QuadtreeNode();
   	};


 		QuadtreeNode* root;    // pointer to root of quadtree

 		//resolution
 		int res;

 		//helper function for copy constructor
 		QuadtreeNode* copy(QuadtreeNode* subRoot);

 		//helper function for destructor
 		void clear(QuadtreeNode*& subRoot);

 		//helper function for buildTree
 		void build(QuadtreeNode*& subRoot, int xCoord, int yCoord, PNG const & source, int resolution);

 		//helper function for getPixel
 		RGBAPixel helpGetPixel(int x, int y, int resolution, QuadtreeNode* subRoot)const;

 		//helper function for decompress
 		void decompress(int x, int y, int resolution, QuadtreeNode* subRoot,PNG &output)const;

    //helper function for clockwiseRotate
 		void rotate(QuadtreeNode*& subRoot);

    //helper function for prune
 		bool diff(QuadtreeNode*& tempNode, QuadtreeNode*& subRoot, int tolerance);

    //helper function for prune
 		void prune(QuadtreeNode*& subRoot, int tolerance);

    //helper function for pruneSize
 		int pruneSize(QuadtreeNode* const & subRoot,int tolerance) const;

    //helper function for pruneSize
 		bool diff2(QuadtreeNode* const & currRoot, QuadtreeNode* const & subRoot, int tolerance)const;

    //helper function for idealPrune
    int ideal(int minimum,int maximum,int numLeaves) const;


 	/**** Functions added for testing/grading                ****/
 	/**** Do not remove this line or copy its contents here! ****/
 	#include "quadtree_given.h"
 };

 #endif
