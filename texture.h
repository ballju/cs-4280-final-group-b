#ifndef __TEXTURE_H
#define __TEXTURE_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

/*
	TEXTURE.H

	The CTexture class
	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 3/29/2001
	Description: The CTexture class represents a single texture
			   object in the engine. To load a texture,
			   you only need to call the LoadTexture() function.

*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>

#define BITMAP_ID 0x4D42		// the universal bitmap ID

enum texTypes_t
{
	PCX,
	BMP,
	TGA
};

// only partial pcx file header
typedef struct
{
	unsigned char manufacturer;
	unsigned char version;
	unsigned char encoding;
	unsigned char bits;
	unsigned char xMin;
	unsigned char yMin;
	unsigned char xMax;
	unsigned char yMax;
	unsigned char *palette;
} PCXHEADER;

typedef struct
{
	unsigned char imageTypeCode;
	short int imageWidth;
	short int imageHeight;
	unsigned char bitCount;
} TGAHEADER;

class CTexture
{
private:
	long int scaledWidth;
	long int scaledHeight;

	unsigned char *palette;

	unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
	unsigned char *LoadBitmapFileWithAlpha(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
	unsigned char *LoadPCXFile(char *filename, PCXHEADER *pcxHeader);
	unsigned char *LoadTGAFile(char *filename, TGAHEADER *tgaHeader);
	void LoadPCXTexture(char *filename);
	void LoadBMPTexture(char *filename);
	void LoadTGATexture(char *filename);

public:
	texTypes_t textureType;
	unsigned char tgaImageCode;	// 0 = not TGA image, 2 = color, 3 = greyscale

	int width;
	int height;
	int bitDepth;
	unsigned int texID;

	unsigned char *data;

	CTexture() { data = NULL; palette = NULL; }
	~CTexture() { Unload(); }

	void LoadTexture(char *filename);
	void Unload()
	{
		glDeleteTextures(1, &texID);

		if (data != NULL)
			free(data);
		if (palette != NULL)
			free(palette);
		
		data = NULL;
		palette = NULL;
	}
};

#endif