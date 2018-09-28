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
//----------------------------------------------------------------------------------------------------
#include "ARS_Utils.h"
#include "GCXObjects.h"
#include "ARS_Material.h"
#include "GCX.h"
//----------------------------------------------------------------------------------------------------
using namespace GCX_OBJECTS;
using namespace GCX;

//----------------------------------------------------------------------------------------------------
namespace ARS_GCXInterface{
	//----------------------------------------------------------------------------------------------------
	// Para aplicar propriedades de reflexão de luz do objeto
	ARS_Material _CurrentObjectMaterial;
	//----------------------------------------------------------------------------------------------------
	int DrawAllGCXObjects(double time);
	int UpdateGCXLight(double time);
	int DrawVectorArray(TFace* poly, TPonto normal, TCor* color);
	//----------------------------------------------------------------------------------------------------
	int UpdateGCXLight(double time){
		_CurrentLight.UpdateLight(time);
		return 0;
	}
	//----------------------------------------------------------------------------------------------------
	int DrawAllGCXObjects(double time){
		 TPonto normal;

		 // Determina normal de cada face e desenha objeto na tela
		 for (int i=1; i <= TB.nf; i++){
			DeterminaNormal(TF[i], normal);
			DrawVectorArray(&TF[i], normal, &TC[TF[i].cor]);
		 }

		return 0;
	}
	//----------------------------------------------------------------------------------------------------
	// Controle de vertices
	int DrawVectorArray(TFace* poly, TPonto normal, TCor* color){
		// Prepara pontos do GCX para desenhar
		int vertexCount = poly->np;

		// Aux para desenhar ( deve ser desalocado depois )
		// Cada vertice possui 3 coordenadas por isso multiplicar o tamanho do _VertexArray por 3
		GLfloat* _VertexArray = new GLfloat[vertexCount*3];
		
		// Vetor normal ( deve ser desalocada depois )
		GLfloat* _Normal = new GLfloat[vertexCount*3];

		// Inteiro utilizado para inserir pontos corretamente no vertex array
		int VertexArrayPosition = 0;
		for(int i = 1; i <= vertexCount; i++){
			//printf("%f %f %f\n", (GLfloat)_GCX_3D_POINT_VECTOR[poly->p[i]].x, (GLfloat)_GCX_3D_POINT_VECTOR[poly->p[i]].y, (GLfloat)_GCX_3D_POINT_VECTOR[poly->p[i]].z);

			// TP3 -> lista de pontos tridimensionais
			_VertexArray[VertexArrayPosition]   = (GLfloat)TP3[poly->p[i]].x;
			_VertexArray[VertexArrayPosition+1] = (GLfloat)TP3[poly->p[i]].y;
			_VertexArray[VertexArrayPosition+2] = (GLfloat)TP3[poly->p[i]].z;

			// Vetor normal da face
			_Normal[VertexArrayPosition]   = normal.x;
			_Normal[VertexArrayPosition+1] = normal.y;
			_Normal[VertexArrayPosition+2] = normal.z;

			VertexArrayPosition += 3;
		}

		// Configurando e aplicando material
		_CurrentObjectMaterial.setAmbientDifuse(color->rgb[1] / 100.0f, color->rgb[2]/ 100.0f, color->rgb[3]/ 100.0f, 1.0f);
		_CurrentObjectMaterial.setSpecular     (color->rgb[4] / 100.0f, color->rgb[5]/ 100.0f, color->rgb[6]/ 100.0f, 1.0f);
		_CurrentObjectMaterial.setShininess    (2);

		_CurrentObjectMaterial.ApplyMaterial();

		// Configura estados 
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glNormalPointer(GL_FLOAT, 0, _Normal);
		glVertexPointer(3, GL_FLOAT, 0, _VertexArray);

		glPushMatrix();     
		
		glBindTexture(GL_TEXTURE_2D, NULL);
		glDrawArrays(GL_POLYGON, 0, vertexCount);

		glPopMatrix();

		glDisableClientState(GL_VERTEX_ARRAY);  // disable vertex arrays
		glDisableClientState(GL_NORMAL_ARRAY);

		// Desalocando vetores
		delete []_VertexArray;
		delete []_Normal;

		return 0;
	}
}
