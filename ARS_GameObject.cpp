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
#include "ARS_GameObject.h"
//----------------------------------------------------------------------------------------------------
ARS_GameObject::ARS_GameObject(void)
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	origin.x = 0.0f;
	origin.y = 0.0f;
	origin.z = 0.0f;
	angleOrigin.x = 0.0f;
	angleOrigin.y = 0.0f;
	angleOrigin.z = 0.0f;
	scale = 1.0f;
	rotationAngle.x = 0.0f;
	rotationAngle.y = 0.0f;
	rotationAngle.z = 0.0f;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
}
//----------------------------------------------------------------------------------------------------
ARS_GameObject::~ARS_GameObject(void)
{
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
	origin.x = 0.0f;
	origin.y = 0.0f;
	origin.z = 0.0f;
	angleOrigin.x = 0.0f;
	angleOrigin.y = 0.0f;
	angleOrigin.z = 0.0f;
	scale = 1.0f;
	rotationAngle.x = 0.0f;
	rotationAngle.y = 0.0f;
	rotationAngle.z = 0.0f;
	rotation.x = 0.0f;
	rotation.y = 0.0f;
	rotation.z = 0.0f;
}
//----------------------------------------------------------------------------------------------------
float& ARS_GameObject::getX()
{
	return position.x;
}
//----------------------------------------------------------------------------------------------------
float& ARS_GameObject::getY()
{
	return position.y;
}
//----------------------------------------------------------------------------------------------------
float& ARS_GameObject::getZ()
{
	return position.z;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getOriginX()
{
	return origin.x;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getOriginY()
{
	return origin.y;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getOriginZ()
{
	return origin.z;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationAngleX()
{
	return rotationAngle.x;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationAngleY()
{
	return rotationAngle.y;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationAngleZ()
{
	return rotationAngle.z;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationOriginX()
{
	return angleOrigin.x;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationOriginY()
{
	return angleOrigin.y;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationOriginZ()
{
	return angleOrigin.z;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationX()
{
	return rotation.x;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationY()
{
	return rotation.y;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getRotationZ()
{
	return rotation.z;
}
//----------------------------------------------------------------------------------------------------
float ARS_GameObject::getScale()
{
	return scale;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setScale(float value)
{
	scale = value;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setRotationOrigin(float angleX, float angleY, float angleZ)
{
	angleOrigin.x = angleX;
	angleOrigin.y = angleY;
	angleOrigin.z = angleZ;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setOrigin_X(float x)
{
	origin.x = x;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setOrigin_Y(float y)
{
	origin.y = y;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setOrigin_Z(float z)
{
	origin.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setOrigin_XY(float x, float y)
{
	origin.x = x;
	origin.y = y;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setOrigin_XZ(float x, float z)
{
	origin.x = x;
	origin.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setOrigin_YZ(float y, float z)
{
	origin.y = y;
	origin.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setOrigin(float x, float y, float z)
{
	origin.x = x;
	origin.y = y;
	origin.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setPosition_X(float x)
{
	position.x = x;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setPosition_Y(float y)
{
	position.y = y;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setPosition_Z(float z)
{
	position.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setPosition_XY(float x, float y)
{
	position.x = x;
	position.y = y;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setPosition_XZ(float x, float z)
{
	position.x = x;
	position.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setPosition_YZ(float y, float z)
{
	position.y = y;
	position.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::setPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::incrementRotAngleX(float inc)
{
	if(rotationAngle.x >= 360)
		rotationAngle.x = 0.0f;
	if(rotationAngle.x <= -360)
		rotationAngle.x = 0.0f;
	rotationAngle.x += inc;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::incrementRotAngleY(float inc)
{
	if(rotationAngle.y >= 360)
		rotationAngle.y = 0.0f;
	if(rotationAngle.y <= -360)
		rotationAngle.y = 0.0f;
	rotationAngle.y += inc;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::incrementRotAngleZ(float inc)
{
	if(rotationAngle.z >= 360)
		rotationAngle.z = 0.0f;
	if(rotationAngle.z <= -360)
		rotationAngle.z = 0.0f;
	rotationAngle.z += inc;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::increment_X(float value)
{
	position.x += value;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::increment_Y(float value)
{
	position.y += value;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::increment_Z(float value)
{
	position.z += value;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::rotateX(float inc, float amount)
{
	incrementRotAngleX(inc);
	rotation.x = amount;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::rotateY(float inc, float amount)
{
	incrementRotAngleY(inc);
	rotation.y = amount;
}
//----------------------------------------------------------------------------------------------------
void ARS_GameObject::rotateZ(float inc, float amount)
{
	incrementRotAngleZ(inc);
	rotation.z = amount;
}

