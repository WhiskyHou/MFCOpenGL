#include "stdafx.h"
#include "GLDraw.h"



GLDraw::GLDraw()
{
	x = 0;
	y = 0;
	z = 0;
	xRot = 0;
	yRot = 0;
	head_rot = 0;
}


GLDraw::~GLDraw()
{
}

void GLDraw::RenderScene(int w, int h)
{
	
	//设置清屏颜色为黑色  
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//清除颜色缓冲区和深度缓冲区  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//透视投影变换  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (double)w / (double)h, 10, 1000);
	//视角变换  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10+x, 10+y, 10+z, 0, 0, 0, 1, 0, 0);
	//矩阵堆栈函数，和glPopMatrix()相对应  
	glPushMatrix();

	glBegin(GL_LINES);
	glColor3d(1.0, 0.0, 0.0);   // X轴 红色  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(3.0, 0.0, 0.0);
	glColor3d(0.0, 1.0, 0.0);   // Y轴 绿色  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 2.0, 0.0);
	glColor3d(0.0, 0.0, 1.0);   // Z轴 蓝色  
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 2.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3d(0.5, 0.5, 0.5);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(0, 1, 0);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glutWireCube(0.5);

	glPopMatrix();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
	
}

void GLDraw::updateX(int nx)
{
	x += nx;
}

void GLDraw::updateY(int ny)
{
	y += ny;
}

void GLDraw::updateZ(int nz)
{
	z += nz;
}

void GLDraw::RenderScene3(int w, int h)
{

	//设置清屏颜色为黑色  
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//清除颜色缓冲区和深度缓冲区  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//透视投影变换  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)w / (double)h, 1, 1000);
	//视角变换  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15 + x, 10 + y, 15 + z, 0, 0, 0, 0, 1, 0);
	//矩阵堆栈函数，和glPopMatrix()相对应  


	glPushMatrix();
	glRotatef(head_rot, 0.0, 1.0, 0.0);
	if (head_rot == 360.0f)head_rot = 0.0f;
	//炮塔
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, map.texture);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0); glVertex3f(1, 4, 2);
	glTexCoord2f(1.0, 1.0); glVertex3f(1, 4, -2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1, 4, -2);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1, 4, 2);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, map.texture);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0); glVertex3f(2, 2, 3);
	glTexCoord2f(1.0, 1.0); glVertex3f(1, 4, 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1, 4, 2);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2, 2, 3);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, map.texture);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0); glVertex3f(2, 2, -3);
	glTexCoord2f(1.0, 1.0); glVertex3f(1, 4, -2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1, 4, -2);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2, 2, -3);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, map.texture);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0); glVertex3f(2, 2, 3);
	glTexCoord2f(1.0, 1.0); glVertex3f(1, 4, 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(1, 4, -2);
	glTexCoord2f(0.0, 0.0); glVertex3f(2, 2, -3);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, map.texture);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0); glVertex3f(-2, 2, 3);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1, 4, 2);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1, 4, -2);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2, 2, -3);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.2, 3, 12);
	glVertex3f(0.2, 3.4, 12);
	glVertex3f(-0.2, 3.4, 12);
	glVertex3f(-0.2, 3, 12);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.2, 3, 12);
	glVertex3f(0.2, 3.4, 12);
	glVertex3f(0.2, 3.4, 0);
	glVertex3f(0.2, 3, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(-0.2, 3, 12);
	glVertex3f(-0.2, 3.4, 12);
	glVertex3f(-0.2, 3.4, 0);
	glVertex3f(-0.2, 3, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.2, 3, 12);
	glVertex3f(-0.2, 3, 12);
	glVertex3f(-0.2, 3, 0);
	glVertex3f(0.2, 3, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.3);
	glVertex3f(0.2, 3.4, 12);
	glVertex3f(-0.2, 3.4, 12);
	glVertex3f(-0.2, 3.4, 0);
	glVertex3f(0.2, 3.4, 0);
	glEnd();

	glPopMatrix();


	//车身
	glPushMatrix();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(3, 2, 5);
	glVertex3f(3, 2, -4);
	glVertex3f(-3, 2, -4);
	glVertex3f(-3, 2, 5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(4, 0, 7);
	glVertex3f(4, 0, -4);
	glVertex3f(-4, 0, -4);
	glVertex3f(-4, 0, 7);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(4, 0, 7);
	glVertex3f(3, 2, 5);
	glVertex3f(-3, 2, 5);
	glVertex3f(-4, 0, 7);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(4, 0, -4);
	glVertex3f(3, 2, -4);
	glVertex3f(-3, 2, -4);
	glVertex3f(-4, 0, -4);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(4, 0, 7);
	glVertex3f(3, 2, 5);
	glVertex3f(3, 2, -4);
	glVertex3f(4, 0, -4);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(-4, 0, 7);
	glVertex3f(-3, 2, 5);
	glVertex3f(-3, 2, -4);
	glVertex3f(-4, 0, -4);
	glEnd();
	


	glPopMatrix();
	glFinish();
	SwapBuffers(wglGetCurrentDC());
}

void GLDraw::updateHeadRot(float r)
{
	head_rot += r;
}
