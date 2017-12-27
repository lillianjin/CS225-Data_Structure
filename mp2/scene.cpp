#include<iostream>
#include "rgbapixel.h"
#include "image.h"
#include "png.h"
#include "scene.h"
using namespace std;

Scene::Scene(int a)
{
  //max is the member function in scene.h
  max=a;
  maximage=new Image*[max];
  xcoords=new int[max];
  ycoords=new int[max];

  for(int i=0; i<max; i++)
  {
  maximage[i]=NULL;
  }
}

Scene::~Scene()
{
  clear();
}

Scene::Scene(const Scene & source)
{
  copy(source);
}

const Scene& Scene::operator=(const Scene& source)
{
  //check to provide self assignment
  //if is self assignment, delete the source data and make an independent copy
  if(this!=&source)
  {
    clear();
    copy(source);
    return *this;
  }
  else
  return *this;
}

void Scene::changemaxlayers(int newmax)
{
  //check if there is non-null pointers outside newmax-1
  if(newmax<max)
  {
    for(int i=newmax;i<max;i++)
    {
      if(maximage[i]!=NULL)
      {
        cout << "invalid newmax" << endl;
        return;
      }
    }
  }

  Image** tempimage=new Image*[newmax];
  int* tempxcoords=new int[newmax];
  int* tempycoords=new int[newmax];

//for max>=newmax
if(max>=newmax)
{
for(int i=0;i<newmax;i++)
  {
    if (maximage[i]!=NULL)
    {
      tempimage[i]=maximage[i];
      tempxcoords[i]=xcoords[i];
      tempycoords[i]=ycoords[i];
    }
    else
    {
      tempimage[i]=NULL;
      tempxcoords[i]=0;
      tempycoords[i]=0;
    }
  }
}

//for max<newmax
else
{
	for(int i=0; i<max ; i++)
		{
      if (maximage[i]!=NULL)
      {
        tempimage[i]=maximage[i];
        tempxcoords[i]=xcoords[i];
        tempycoords[i]=ycoords[i];
      }
      else
      {
        tempimage[i]=NULL;
        tempxcoords[i]=0;
        tempycoords[i]=0;
      }
		}

  for(int j=max; j<newmax; j++)
			{
			tempimage[j]=NULL;
      tempxcoords[j]=0;
      tempycoords[j]=0;
			}
	}

  //free memory
  delete []maximage;
  delete []xcoords;
  delete []ycoords;

  //make an assignment from tempimage to maximage
  max=newmax;
  maximage=tempimage;
  xcoords=tempxcoords;
  ycoords=tempycoords;

  tempimage=NULL;
  tempxcoords=NULL;
  tempycoords=NULL;

}


void Scene::addpicture(const char* Filename, int index, int x, int y)
{
  if(index>max-1||index<0)
  {
    cout << "index out of bounds" << endl;
    return;
  }
  else
  {
    //store the x and y coordinates
    xcoords[index]=x;
    ycoords[index]=y;

    if(maximage[index]!=NULL)
    {
      delete maximage[index];
    }
    else
    //read the taget picture
    {
      Image* picture=new Image();
      picture->readFromFile(Filename);
      maximage[index]=picture;
    }
  }
}


void Scene::changelayer(int index, int newindex)
{
  if(index>max-1||index<0||newindex>max-1||newindex<0)
    {
      cout << "invalid index" << endl;
      return;
    }

  if(index==newindex)
  {
    return;
  }

  xcoords[newindex]=xcoords[index];
  ycoords[newindex]=ycoords[index];

  //If the destination is already occupied, delete the image there.
  //The source index should be marked vacant by making it value NULL.
  if(maximage[newindex]!=NULL)
  {
    delete maximage[newindex];
  }

  if(maximage[index]!=NULL)
    {
      maximage[newindex]=maximage[index];
      maximage[index]=NULL;
    }
    else
    maximage[newindex]=NULL;
}


void Scene::translate(int index, int xcoord, int ycoord)
{
  if(index>max-1||index<0||maximage[index]==NULL)
    {
      cout << "invalid index" << endl;
      return;
    }
  else
    xcoords[index]=xcoord;
    ycoords[index]=ycoord;
}


void Scene::deletepicture(int index)
{
  if(index>max-1||index<0||maximage[index]==NULL)
    {
      cout << "invalid index" << endl;
      return;
    }
    else
    delete maximage[index];
    maximage[index]=NULL;
}


Image* Scene::getpicture(int index) const
{
  if(index>max-1||index<0||maximage[index]==NULL)
    {
      cout << "invalid index" << endl;
      return NULL;
    }
    else
    return maximage[index];
}

Image Scene::drawscene() const
{
  size_t width=0;
  size_t height=0;

  for(int x=0; x<max; x++)
  {
    if(maximage[x]!=NULL)
      {
        if(width<(xcoords[x]+maximage[x]->width()))
        {
          width=xcoords[x]+maximage[x]->width();
        }
        if(height<(ycoords[x]+maximage[x]-> height()))
        {
          height=ycoords[x]+maximage[x]->height();
        }
      }
  }

  Image output;
  output.resize(width, height);

  for(int y=0; y<max; y++)
  {
    if(maximage[y]!=NULL)
    {
      for(size_t i=0; i<maximage[y]->width();i++)
      {
        for(size_t j=0; j<maximage[y]->height();j++)
        {
          output(xcoords[y]+i,ycoords[y]+j)->red=(*maximage[y])(i,j)->red;
          output(xcoords[y]+i,ycoords[y]+j)->green=(*maximage[y])(i,j)->green;
          output(xcoords[y]+i,ycoords[y]+j)->blue=(*maximage[y])(i,j)->blue;
        }
      }
    }
  }
  return output;
}


void Scene::clear()
{
  delete[] xcoords;
  xcoords=NULL;
  delete[] ycoords;
  ycoords=NULL;

  for(int i=0; i<max; i++)
	{
	   if (maximage[i]!=NULL)
		{
			delete maximage[i];
			maximage[i] = NULL;
		}
	}

  delete[] maximage;
  maximage=NULL;
}


void Scene::copy(const Scene& source)
{
  max=source.max;
  xcoords=new int [max];
  ycoords=new int [max];
  maximage=new Image* [max];

for(int i=0; i<max; i++)
  {
    xcoords[i]=source.xcoords[i];
    ycoords[i]=source.ycoords[i];

    if(source.maximage[i]!=NULL)
    {
      maximage[i]=new Image (*(source.maximage[i]));
    }
    else
    maximage[i]=NULL;
  }
}
