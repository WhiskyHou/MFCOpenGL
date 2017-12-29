#include "stdafx.h"
#include "LoadMap.h"


LoadMap::LoadMap()
{
	texture = 0;
	imageData = NULL;
	width = 0;
	height = 0;
}


LoadMap::~LoadMap()
{
}

void LoadMap::init()
{
	imageData = openBMP("map_300.bmp");
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
}

unsigned char * LoadMap::openBMP(const char* path)
{
	unsigned char* imageData = nullptr;
	FILE* pFile;
	fopen_s(&pFile, path, "rb");
	if (pFile)
	{
		TRACE("open win");
		BITMAPFILEHEADER bfh;
		fread(&bfh, sizeof(BITMAPFILEHEADER), 1, pFile);
		if (bfh.bfType == 0x4D42)
		{
			BITMAPINFOHEADER bih;
			fread(&bih, sizeof(BITMAPINFOHEADER), 1, pFile);
			width = bih.biWidth;
			height = bih.biHeight;
			imageData = new unsigned char[width*height * 3];
			fseek(pFile, bfh.bfOffBits, SEEK_SET);
			fread(imageData, 1, width*height * 3, pFile);
			fclose(pFile);
		}
	}
	if (imageData == NULL)
	{
		TRACE("open filled");
	}
	return imageData;
}
