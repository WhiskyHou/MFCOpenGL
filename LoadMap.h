#pragma once
#include"stdafx.h"

class LoadMap
{
public:
	GLuint texture;
	unsigned char* imageData;
	int width;
	int height;
public:
	LoadMap();
	~LoadMap();
	void init();
	unsigned char* openBMP(const char* path);
};

