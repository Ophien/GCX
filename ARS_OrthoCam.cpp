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
#include "ARS_OrthoCam.h"
#include <math.h>
//----------------------------------------------------------------------------------------------------
ARS_OrthoCam::ARS_OrthoCam(void) : ARS_Camera()
{
	setPosition(0.0f,0.0f,0.0f);
	zoom = 1.0f;
	moveFactor = 200.0f;
	mZoomState = idle;
	_Rotation.x = 0.0f;
	_Rotation.y = 0.0f;
	_Rotation.z = 0.0f;
}
//----------------------------------------------------------------------------------------------------
ARS_OrthoCam::~ARS_OrthoCam(void)
{
}
//----------------------------------------------------------------------------------------------------
void ARS_OrthoCam::lockTarget2D()
{
	gluLookAt(
		getX(), getY(), getZ(),
		target->getX(), target->getX(), 
		0, 0.0f, 1.0f, 0.0f);
}
//----------------------------------------------------------------------------------------------------
void ARS_OrthoCam::look2D()
{
	gluLookAt(
		getX(), getY(), getZ(),
		getX(), getY(), 0.0f,
		0.0f, 1.0f, 0.0f);
}
//----------------------------------------------------------------------------------------------------
void ARS_OrthoCam::move()
{
	vec2 _invDelta;
	vec2 _deltaMove;
	if(_cameraMove){
		if(mouse.buttonPress)
			switch(mouse._lastButton){
			case GLUT_RIGHT_BUTTON:
				_invDelta = mouse.getInvertDelta();

				_invDelta /= zoom;

				increment_X(_invDelta.x);
				increment_Y(_invDelta.y);
				updateView();
				break;
		}
	}
}
//----------------------------------------------------------------------------------------------------
void ARS_OrthoCam::update()
{
	if(_zoomEnable){
		if(mouse.mouseWheelPos > mouse.pMouseWheelPos){
			if(zoom < MAX_ZOOM){
				mZoomState = zooming;
				zoom+=0.03f;
				if(zoom > MAX_ZOOM)
					zoom = (float)MAX_ZOOM;
			}
		}else{
			if(zoom>MIN_ZOOM){
				mZoomState = zooming;
				zoom-=0.03f;
				if(zoom < MIN_ZOOM)
					zoom = (float)MIN_ZOOM;
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------
void ARS_OrthoCam::initializePosition()
{
	look2D();
}
//----------------------------------------------------------------------------------------------------
void ARS_OrthoCam::updateView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window.width, window.height, 0, nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(zoom, zoom, zoom);
	look2D();
}
