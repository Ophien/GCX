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
#pragma once

#include "ARS_Utils.h"

class ARS_Material
{
public:
	ARS_Material(void);
	~ARS_Material(void);

	void ApplyMaterial();

	// Gets and sets
	void setAmbientDifuse(float r, float g, float b, float a){_AmbientDifuse = vec4(r,g,b,a);}
	void setSpecular(float r, float g, float b, float a){_Specular = vec4(r,g,b,a);}
	void setShininess(float _Value){_SpecularShininess = _Value;}

	vec4* getAmbientDifuse(){return &_AmbientDifuse;}
	vec4* getSpecular()     {return &_Specular;}
	float* getShininess()   {return &_SpecularShininess;}

private:

	// wavelenght refletido
	vec4  _AmbientDifuse;
	vec4  _Specular;
	float _SpecularShininess;
};

