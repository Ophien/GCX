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
#include "ARS_Utils.h"
#include "ARS_WindowInf.h"
//----------------------------------------------------------------------------------------------------
using namespace ARS_WindowInf;
//----------------------------------------------------------------------------------------------------
class Mouse{
public:
	bool buttonPress;
	bool singleButtonPress;

	int _lastButton;
	int _previousButton;
	vec2 pMousePos;
	vec2 mousePos;
	vec4 worldPosition;
	int pMouseWheelPos;
	int mouseWheelPos;
	int _lastButtonState;
	int _previousButtonState;

	Mouse(){
		_lastButton = 0;
		_previousButton = 0;
		pMousePos = 0;
		mousePos.x = 0;
		mousePos.y = 0;
		pMouseWheelPos = 0;
	}
	//----------------------------------------------------------------------------------------------------
	vec3 getWindowRelPosition()
	{
		vec3 windowRelPosition(mousePos.x, mousePos.y, 0);
		return windowRelPosition;
	}
	//----------------------------------------------------------------------------------------------------
	vec3 getWorldPosition()
	{
		mat4 mMat = inv(getModelviewFromGL());
		windowToWorld();
		vec4 worldPoint = mMat*worldPosition;
		vec3 worldPos;
		worldPos.x = worldPoint.x;
		worldPos.y = worldPoint.y;
		worldPos.z = 0;
		return worldPos;
	}
	//----------------------------------------------------------------------------------------------------
	void windowToWorld()
	{
		float Py, Px;
		Py = 2*(-(float)mousePos.y/((float)window.height-1));
		Px = 2*(((float)mousePos.x/((float)window.width-1))-((float)window.width/(float)window.height));
		worldPosition.x = Px;
		worldPosition.y = Py;
		worldPosition.z = 0;
		worldPosition.w = 1;
	}
	//----------------------------------------------------------------------------------------------------
	bool getMouseRay(vec3 *pos, vec3 *dir)
	{
		//vec3 worldPosition;
		/*if (GL_unproject(getWindowRelPosition(), &worldPosition)){
			vec3 mCamPos = toVec3(getModelviewFromGL()*vec4(0,0,0,1));
			*dir = normalize(worldPosition-mCamPos);
			*pos = mCamPos;
			return true;
		}*/
		return false;
	}
	//----------------------------------------------------------------------------------------------------
	vec3 GetOGLPos(float x, float y)
	{
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX, winY, winZ;
		GLdouble posX, posY, posZ;

		glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
		glGetDoublev( GL_PROJECTION_MATRIX, projection );
		glGetIntegerv( GL_VIEWPORT, viewport );

		winX = (float)x;
		winY = (float)viewport[3] - (float)y;
		winZ = 0;
		gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
		return vec3((float)posX,(float)posY,(float)posZ);
	}
	//----------------------------------------------------------------------------------------------------
	vec2 getInvertDelta()
	{
		vec2 res = pMousePos - mousePos;
		return res;
	}
	//----------------------------------------------------------------------------------------------------
	vec2 getDelta()
	{
		vec2 res = mousePos - pMousePos;
		return res;
	}
};
//----------------------------------------------------------------------------------------------------
class Keyboard{
public:
	bool singlePress;
	bool singleCharPress;
	bool press;
	bool charPress;

	int _lastKey;
	int _previousKey;
	int _lastKeyState;
	int _previousKeyState;

	int _lastCharKey;
	int _previousCharKey;
	int _lastCharKeyState;
	int _previousCharKeyState;

	Keyboard(){
		_lastKey = 0;
		_previousKey = 0;
		//_lastKeyState = GLUT_UP;
		//_previousKeyState = GLUT_UP;

		_lastCharKey = 0;
		_previousCharKey = 0;
		//_lastCharKeyState = GLUT_UP;
		//_previousCharKeyState = GLUT_UP;
	}
};
//----------------------------------------------------------------------------------------------------
namespace ARS_Input{
	extern Mouse mouse;
	extern Keyboard keyboard;
}

