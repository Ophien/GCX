/*MIT License
*
*Copyright (c) 2018 Alysson Ribeiro da Silva
*
*Permission is hereby granted, free of charge, to any person obtaining a copy 
*of this software and associated documentation files (the "Software"), to deal 
*in the Software without restriction, including *without limitation the rights 
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
*copies of the Software, and to permit persons to whom the Software is furnished 
*to do so, subject *to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
*EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *IN NO EVENT SHALL THE AUTHORS 
*OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
*AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
*THE *SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
//----------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------

#include "basis.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "vecOP.h"
#include "mat4.h"
#include "AABB.h"
#include "blerp.h"
#include "splineCatmullRom.h"
#include "glut.h"
//----------------------------------------------------------------------------------------------------
#define CONTENT "content/"
//----------------------------------------------------------------------------------------------------
class _wh{
public:
	GLuint width;
	GLuint height;
	float  scale;

	_wh(GLuint widthP = 0, GLuint heightP = 0, float _scale = 1.0f){
		width = widthP;
		height = heightP;
		scale = _scale;
	}
};
//----------------------------------------------------------------------------------------------------
class Source{
public:
	_wh wh;
	float x, y, x1, y1, x2, y2, x3, y3, deslocX, deslocY;
	vec2 pos;

	Source(
		_wh whP = 0,
		vec2 posP = 0,
		float xP = 0,
		float x1P = 0, 
		float x2P = 1,
		float x3P = 0, 
		float yP = 0, 
		float y1P = 1,
		float y2P = 0, 
		float y3P = 0,
		float deslocXP = 0,
		float deslocYP = 0){
			wh = whP;
			posP = pos;
			x = xP;
			x1 = xP;
			x2 = x2P;
			x3 = x3P;
			y = yP;
			y1 = y1P;
			y2 = yP;
			y3 = y3P;
			deslocX = deslocXP;
			deslocY = deslocYP;
	}
};
//----------------------------------------------------------------------------------------------------
static void ARS_HudBegin()
{
	int vPort[4];
	glDisable(GL_LIGHTING);// Desliga iluminação do hud
	glGetIntegerv(GL_VIEWPORT, vPort);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, vPort[2], vPort[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1,1,1);

}
//----------------------------------------------------------------------------------------------------
static void ARS_HudEnd(){
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);// Liga iluminação global 
}
//----------------------------------------------------------------------------------------------------
