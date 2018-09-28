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
#include "ARS_PerspectiveCam.h"
#include <math.h>
//----------------------------------------------------------------------------------------------------
ARS_PerspectiveCam::ARS_PerspectiveCam(void) : ARS_Camera()
{
	setPosition(0.0f,0.0f,0.0f);
	zoom = 1.0f;
	moveFactor = 200.0f;
	mZoomState = idle;
	_Rotation.x = 0.0f;
	_Rotation.y = 0.0f;
	_Rotation.z = 0.0f;
	theta = 0.0f;
	phi = 0.0f;
}
//----------------------------------------------------------------------------------------------------
ARS_PerspectiveCam::~ARS_PerspectiveCam(void)
{
}
//----------------------------------------------------------------------------------------------------
void ARS_PerspectiveCam::lockTarget2D()
{
	gluLookAt(
		getX(), getY(), getZ(),
		target->getX(), target->getX(), 
		0, 0.0f, 1.0f, 0.0f);
}
//----------------------------------------------------------------------------------------------------
void ARS_PerspectiveCam::look2D()
{
	//float radius = getZ();
    //vec3 rotationPos = vec3(radius*cos(phi)*-sin(theta), 
	//	                    radius*-sin(phi)*sin(theta),
	//						radius*cos(theta));

	gluLookAt(
		getX(), getY(), getZ(),
		getX(), getY(), 0.0f,
		0.0f, 1.0f, 0.0f);
}
//----------------------------------------------------------------------------------------------------
void ARS_PerspectiveCam::move()
{
	/*vec2 _delta;
	if(_cameraMove){
		if(mouse.buttonPress)
			switch(mouse._lastButton){
			case GLFW_MOUSE_BUTTON_RIGHT:
				_delta = mouse.getInvertDelta();

				  theta += _delta.x*0.01f;
				  phi   += _delta.y*0.01f;

				break;
		}
	}*/
}
//----------------------------------------------------------------------------------------------------
void ARS_PerspectiveCam::update(double time)
{
	float incrementFactor = 500.0f;

/*	if(_cameraMove){
		if(glutGetKey('A') == GLUT_DOWN){
			increment_X(incrementFactor*-1*time);
		}
		if(glfwGetKey('D') == GLUT_DOWN){
			increment_X(incrementFactor*time);
		}
		if(glfwGetKey('W') == GLUT_DOWN){
			increment_Y(incrementFactor*time);
		}
		if(glfwGetKey('S') == GLUT_DOWN){
			increment_Y(incrementFactor*-1*time);
		}
	}*/
}
//----------------------------------------------------------------------------------------------------
void ARS_PerspectiveCam::update(){
	if(_zoomEnable){
		if(mouse.mouseWheelPos > mouse.pMouseWheelPos){
			increment_Z(-100.0f);
		}else{
			increment_Z(100.0f);
		}
	}
}
//----------------------------------------------------------------------------------------------------
void ARS_PerspectiveCam::initializePosition()
{
	look2D();
}
//----------------------------------------------------------------------------------------------------
void ARS_PerspectiveCam::updateView()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float)window.width / (float)window.height, nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(zoom, zoom, zoom);
	look2D();
}
