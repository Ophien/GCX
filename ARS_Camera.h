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
#include <string>
#include "glut.h"
#include "ARS_Input.h"
#include "ARS_GameObject.h"
#include "ARS_Object.h"
//----------------------------------------------------------------------------------------------------
using namespace std;
using namespace ARS_Input;
//----------------------------------------------------------------------------------------------------
#define MAX_ZOOM 100
#define MIN_ZOOM 0.1
//----------------------------------------------------------------------------------------------------
enum zoomState
{
	zooming,
	idle
};
//----------------------------------------------------------------------------------------------------
class ARS_Camera : public ARS_GameObject, ARS_Object
{
protected:
	string name;
	ARS_GameObject* target;
	unsigned char up, down, left, right;
	unsigned int fov;
	float nearPlane;
	float farPlane;
	float zoom;
	float moveFactor;
	void setTarget(ARS_GameObject* target);
	void setFov(unsigned int fov);
	void setPlanes(float nearPlane, float farPlane);
	void setNearPlane(float nearPlane);
	void setFarPlane(float farPlane);
	void setZDistance(float value);
	void incrementZoom(float value);
	zoomState mZoomState;

public:
	void init(unsigned int fov, float nearPlane, float farPlane);
	void setControls(unsigned char up, unsigned char down, unsigned char left, unsigned char right);
	virtual void move()=0;
	virtual void update()=0;
	virtual void update(double time)=0;
	virtual void updateView()=0; 
	virtual void initializePosition()=0;
	void setZoom(float value);
	float getZoom(){return zoom;}
	float* getZoomRef(){return &zoom;}
};

