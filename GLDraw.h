#pragma once
#include"stdafx.h"
#include"LoadMap.h"
class GLDraw
{
public:
	int x;
	int y;
	int z;
	GLfloat xRot;
	GLfloat yRot;
	GLfloat head_rot;
	LoadMap map;
public:
	GLDraw();
	~GLDraw();
	void RenderScene(int , int);
	void updateX(int);
	void updateY(int);
	void updateZ(int);

	void RenderScene3(int,int);

	void updateHeadRot(float);
};

