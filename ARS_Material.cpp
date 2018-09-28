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
#include "ARS_Material.h"
//----------------------------------------------------------------------------------------------------
ARS_Material::ARS_Material(void)
{
	// Valores padrões
	_Specular          = vec4(.8f,.8f,.8f,1.0f);
	_AmbientDifuse     = vec4(.3f,.3f,.3f,1.0f);
	_SpecularShininess = 2;
}
//----------------------------------------------------------------------------------------------------
ARS_Material::~ARS_Material(void)
{
}
//----------------------------------------------------------------------------------------------------
void ARS_Material::ApplyMaterial(){
	// Cor da reflexão specular da face
	// Configura material specular de acordo com o degrade da cor máxima
	GLfloat mat_specular[] = { _Specular.x, 
		                       _Specular.y, 
							   _Specular.z, 
							   _Specular.w};
		
	// Brilho do objeto
	GLfloat low_shininess[] = { _SpecularShininess };
	
	GLfloat mat_ambient_difuse[] = { _AmbientDifuse.x,
									 _AmbientDifuse.y,
	                                 _AmbientDifuse.z,
	                                 _AmbientDifuse.w};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_ambient_difuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,            mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS,           low_shininess);
	// Cor da reflexão specular da face
}
//----------------------------------------------------------------------------------------------------
