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
#include "ARS_Camera.h"
//----------------------------------------------------------------------------------------------------
void ARS_Camera::setControls(unsigned char up, unsigned char down, unsigned char left, unsigned char right)
{
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
}
//----------------------------------------------------------------------------------------------------
void ARS_Camera::incrementZoom(float value)
{
	zoom += value;
}
//----------------------------------------------------------------------------------------------------
void ARS_Camera::setZoom(float value)
{
	zoom = value;
}
//----------------------------------------------------------------------------------------------------
void ARS_Camera::setTarget(ARS_GameObject* target)
{
	target = target;
}
//----------------------------------------------------------------------------------------------------
void ARS_Camera::setFov(unsigned int fov)
{
	this->fov = fov;
}
//----------------------------------------------------------------------------------------------------
void ARS_Camera::setPlanes(float nearPlane, float farPlane)
{
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
}
//----------------------------------------------------------------------------------------------------
void ARS_Camera::setNearPlane(float nearPlane)
{
	this->nearPlane = nearPlane;
}
//----------------------------------------------------------------------------------------------------	
void ARS_Camera::setFarPlane(float farPlane)
{
	this->farPlane = farPlane;
}
//----------------------------------------------------------------------------------------------------
void ARS_Camera::init(unsigned int fov, float nearPlane, float farPlane)
{
	this->fov = fov;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
}
