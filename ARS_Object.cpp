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
#include "ARS_Object.h"
//----------------------------------------------------------------------------------------------------
ARS_Object::ARS_Object(void)
{
}
//----------------------------------------------------------------------------------------------------
ARS_Object::~ARS_Object(void)
{
}
//----------------------------------------------------------------------------------------------------
void ARS_Object::doAllTrasnformations(vec3& position, vec3& origin, float scale, vec3& angleOrigin, vec3& rotationAngle, vec3& rotation)
{
	glRotatef((GLfloat)angleOrigin.x, 1.0, 0.0f, 0.0f);
	glRotatef((GLfloat)angleOrigin.y, 0.0f, 1.0f, 0.0f);
	glRotatef((GLfloat)angleOrigin.z, 0.0f, 0.0f, 1.0f);
	
	glTranslatef((GLfloat)position.x, (GLfloat)position.y, (GLfloat)position.z);

	glRotatef((GLfloat)rotationAngle.x, (GLfloat)rotation.x, 0.0f, 0.0f);
	glRotatef((GLfloat)rotationAngle.y, 0.0f, (GLfloat)rotation.y, 0.0f);
	glRotatef((GLfloat)rotationAngle.z, 0.0f, 0.0f, (GLfloat)rotation.z);

	glTranslatef((GLfloat)origin.x, (GLfloat)origin.y, (GLfloat)origin.z);

    glScalef(scale,scale,scale);
}
