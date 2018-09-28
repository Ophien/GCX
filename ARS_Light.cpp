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
#include "ARS_Light.h"
//----------------------------------------------------------------------------------------------------
ARS_Light::ARS_Light(void)
{
	// Inicializando valores padrões
	_AmbientRGBA  = vec4(.2f, .2f, .2f, 1.0f);
	_DifuseRGBA   = vec4(.8f, .8f, .8f, 1.0f);
	_SpecularRGBA = vec4(.8f, .8f, .8f, 1.0f);
	setPosition(.0f,.0f,.0f);

	// Configurando ID da luz
	_LightID = GL_LIGHT0;
}
//----------------------------------------------------------------------------------------------------
ARS_Light::~ARS_Light(void)
{
}
//----------------------------------------------------------------------------------------------------
void ARS_Light::UpdateLight(double time){
    // set up light colors (ambient, diffuse, specular)
    /*
	GLfloat lightKa[]   = {.2f, .2f, .2f, 1.0f};  // ambient  light
    GLfloat lightKd[]   = {.8f, .8f, .8f, 1.0f};  // diffuse  light
    GLfloat lightKs[]   = {.8f, .8f, .8f, 1.0f};  // specular light
	GLfloat lightPos[]  = {.0f, .0f, .0f, 1.0f};  // position light
	*/
	
	GLfloat lightKa[]   = {_AmbientRGBA.x , _AmbientRGBA.y , _AmbientRGBA.z , _AmbientRGBA.w };  // ambient  light
    GLfloat lightKd[]   = {_DifuseRGBA.x  , _DifuseRGBA.y  , _DifuseRGBA.z  , _DifuseRGBA.w  };  // diffuse  light
    GLfloat lightKs[]   = {_SpecularRGBA.x, _SpecularRGBA.y, _SpecularRGBA.z, _SpecularRGBA.w};  // specular light
	GLfloat lightPos[]  = {getPosition().x, getPosition().y, getPosition().z, 1.0f           };  // position light

	glLightfv(_LightID, GL_AMBIENT, lightKa);
    glLightfv(_LightID, GL_DIFFUSE, lightKd);
    glLightfv(_LightID, GL_SPECULAR, lightKs);
    glLightfv(_LightID, GL_POSITION, lightPos);
}
//----------------------------------------------------------------------------------------------------
void ARS_Light::TurnOff(){
	glDisable(_LightID);
}
//----------------------------------------------------------------------------------------------------
void ARS_Light::TurnOn(){
	glEnable(_LightID);
}
//----------------------------------------------------------------------------------------------------
