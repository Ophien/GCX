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
#include "ARS_GameObject.h"
#include "glut.h"

class ARS_Light : public ARS_GameObject
{
public:
	ARS_Light(void);
	~ARS_Light(void);

	// Atualiza valores da luz
	void UpdateLight(double time);
	
	// Liga desliga
	void TurnOn();
	void TurnOff();

	// Gets and sets
	void setAmbient(vec4 _value) {_AmbientRGBA = _value;}
	void setDifuse(vec4 _value)  {_DifuseRGBA = _value;}
	void setSpecular(vec4 _value){_SpecularRGBA = _value;}

	vec4* getAmbient() {return &_AmbientRGBA;}
	vec4* getDifuse()  {return &_DifuseRGBA;}
	vec4* getSpecular(){return &_SpecularRGBA;}

	void setId(int ID){if(ID >= GL_LIGHT0 && ID <= GL_LIGHT7)_LightID = ID;}

private:
	int _LightID;

	// AMBIENT CONFIG
	vec4 _AmbientRGBA;

	// DIFUSE CONFIG
	vec4 _DifuseRGBA;
	
	// SPECULAR CONFIG
	vec4 _SpecularRGBA;
};

