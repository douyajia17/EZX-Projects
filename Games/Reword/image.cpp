////////////////////////////////////////////////////////////////////
/*

File:			image.cpp

Class impl:		Image

Description:	A class based on the Surface class that encapulates image 
				specific functions. Tile handling is included.

				All Image class surfaces use the transparent pixel (255,0,255)
				which is a putrid purple.

				Surface->Image

Author:			Al McLuckie (al-at-purplepup-dot-org)

Date:			06 April 2007

Licence:		This program is free software; you can redistribute it and/or modify
				it under the terms of the GNU General Public License as published by
				the Free Software Foundation; either version 2 of the License, or
				(at your option) any later version.

				This software is distributed in the hope that it will be useful,
				but WITHOUT ANY WARRANTY; without even the implied warranty of
				MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
				GNU General Public License for more details.

				You should have received a copy of the GNU General Public License
				along with this program; if not, write to the Free Software
				Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/
////////////////////////////////////////////////////////////////////

#include "global.h"
#include "image.h"
#include "utils.h"

#include <iostream>

Image::Image() : 
	Surface(), _init(false)
{
	cleanUp();
}

Image::Image(unsigned int w, unsigned int h, int iAlpha /*=-1*/) : 
	Surface(), _init(false)
{
	cleanUp();
	_init = create(w, h, iAlpha);	//create surface of required size
	setTileSize();					//ensure tile size set (at least to size of image)
}

Image::Image(std::string fileName, int iAlpha /*=-1*/) : 
	Surface(), _init(false)
{
	cleanUp();
	load(fileName, iAlpha);
}

Image::~Image()
{
	cleanUp();
}

void Image::cleanUp()
{
	Surface::cleanUp();	//free surface etc

	_tileW = _tileH = _tileCount = 0;
//	_clip = 0;	//use whole image (used in blit(Image*) )

	_init = false;
}

//return a new image from a tile in this image
Image * Image::createImageFromThis(int tileNum, int iAlpha /*=-1*/)
{
	SDL_Rect r = tile(tileNum, _tileW, _tileH);
	Image *image = new Image(r.w, r.h, iAlpha);
	image->blitFrom(this, tileNum);
	image->setTileSize(_tileW, _tileH);
	return image;
}

//create this image from another image (tile)
void Image::createThisFromImage(Image &image, int tileNum /*=-1*/, int iAlpha /*=-1*/)
{
	cleanUp();
	_init = Surface::create(image.tileW(), image.tileH(), iAlpha);
	//prefill with alpha colour so the final surface contains it where curr see through
	drawSolidRect(0,0,image.tileW(),image.tileH(), ALPHA_COLOUR);
	if (-1 == tileNum) 
		setTileSize(); 
	else 
		setTileSize(image.tileW(), image.tileH());
	blitFrom(&image, tileNum);	//into this newly created 'copy'
}

//set the predefined size of a tile
//Currently tiles in images should be placed horizontally [0,1,2,3,4,5...]
bool Image::setTileSize(int w /*= 0*/, int h /*= 0*/)
{
	if (!initDone()) return false; //can't set dimentions of no image

	if ((h < 1) || (h > _surface->h)) h = _surface->h;	//default to height of image
	if ((w < 1) || (w > _surface->w)) w = _surface->w;	//default to whole width of image

	_tileW = w;
	_tileH = h;
	_tileCount = (int)_surface->w / w;  //for a sanity check in tile() fn

	return true;
}

bool Image::load(std::string fileName, int iAlpha /* =-1 */)
{
	//Temporary storage for the image that's loaded 
	SDL_Surface* loadedImage = NULL; 

	 //Load the image 
//	loadedImage = SDL_LoadBMP( fileName.c_str() );	//using SDL dll
	loadedImage = IMG_Load(fileName.c_str());		//using SDL_Image dll (png, jpg etc)
	if (NULL == loadedImage)
	{
		std::cerr << "Failed to load image " << fileName << ". Cannot start." << std::endl;
		return false;
	}

	return initImage(loadedImage, iAlpha);
}

//use the surface classes initSurface() fn to set up the image surface
bool Image::initImage(SDL_Surface *newSurface, int iAlpha /* =-1 */)
{
	cleanUp();
	_init = Surface::initSurface(newSurface, iAlpha);
	setTileSize(_surface->w, _surface->h);	//default to size of image
	return _init;
}


//assumes a single row of tiles [0,1,2,3,4,5...] 
//static version, returns rect of exactly what is passed in
SDL_Rect Image::tile(int i, int w, int h)	
{
	SDL_Rect rect;
	rect.x = i*w;
	rect.y = 0;
	rect.w = w;
	rect.h = h;
	return rect;
}

//non static version that relies on setTileSize() previously called
SDL_Rect Image::tile(int i)
{
	if (i < 0 || i >= _tileCount) i = 0;
	SDL_Rect rect;
	rect.x = i*_tileW;
	rect.y = 0;
	rect.w = _tileW;
	rect.h = _tileH;
	return rect;
}


//helper blit functions specifically for the Image class wrapping a surface
//
//blit this (tile) image into another image (or screen)
void Image::blitTo(Surface* dest, int destX, int destY, int tileNum /*= -1*/)
{
	//Image class objects default to clip = 0 unless explicitly set
	blit_surface(this->_surface, (tileNum<0)?NULL:&this->tile(tileNum),			//source
				dest->surface(), destX, destY);									//dest
}

//blit a (tile) image into this image
void Image::blitFrom(Image* source, int tileNum /*= -1*/, int destX, int destY )
{
	//Image class objects default to clip = 0 unless explicitly set
	blit_surface(source->surface(), (tileNum<0)?NULL:&source->tile(tileNum),	//source
				this->_surface, destX, destY);									//dest
}

