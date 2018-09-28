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
#include "ARS_Object.h"
#include "ARS_Utils.h"
//----------------------------------------------------------------------------------------------------
class ARS_GameObject
{
public:
	ARS_GameObject(void);
	~ARS_GameObject(void);

	protected:
		vec3 angleOrigin;
		vec3 origin;
		vec3 position;
		float scale;
		vec3 rotationAngle;
		vec3 rotation;
		void incrementRotAngleX(float inc);
		void incrementRotAngleY(float inc);
		void incrementRotAngleZ(float inc);

    public:
		vec3 getPosition(){return position;}
		vec3* getPosRef(){return &position;}
		float* getScaleRef(){return &scale;}
        float& getX();
        float& getY();
     	float& getZ();
		float getOriginX();
        float getOriginY();
     	float getOriginZ();
		float getRotationOriginX();
		float getRotationOriginY();
		float getRotationOriginZ();
		float getRotationAngleX();
		float getRotationAngleY();
		float getRotationAngleZ();
		float getRotationX();
		float getRotationY();
		float getRotationZ();
		float getScale();
		void transform(vec3 desloc){position+=desloc;}
		void setScale(float value);
		void rotateX(float inc, float amount);
		void rotateY(float inc, float amount);
		void rotateZ(float inc, float amount);
		void setRotationOrigin(float angleX, float angleY, float angleZ);
		void setOrigin_X(float x);
		void setOrigin_Y(float y);
		void setOrigin_Z(float z);
		void setOrigin_XY(float x, float y);
		void setOrigin_XZ(float x, float z);
		void setOrigin_YZ(float y, float z);
		void setOrigin(float x, float y, float z);
		void increment_X(float value);
		void increment_Y(float value);
		void increment_Z(float value);
		void setPosition_X(float x);
		void setPosition_Y(float y);
		void setPosition_Z(float z);
		void setPosition_XY(float x, float y);
		void setPosition_XZ(float x, float z);
		void setPosition_YZ(float y, float z);
		void setPosition(float x, float y, float z);
};

