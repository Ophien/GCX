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
#include "GCXConfig.h"
//----------------------------------------------------------------------------------------------------
using namespace GCX_CONFIG;
//----------------------------------------------------------------------------------------------------
namespace GCX_OBJECTS{
	typedef struct TAngulos            /* angulos de rotacao em rad.*/
	{
		double alfa;                   /* rot. eixo z */
		double beta;                   /* rot. eixo x */
		double gama;                   /* rot. eixo y */
		double sa;                     /* sen. alfa */
		double ca;                     /* cos. alfa */
		double sb;                     /* sen. beta */
		double cb;                     /* cos. beta */
		double sg;                     /* sen. gama */
		double cg;                     /* cos. gama */
	}TAngulos;
	//----------------------------------------------------------------------------------------------------
	typedef struct pointtype        /* elemento das tab. pontos */
	{
		int x;                      /* coordenada x */
		int y;                      /* coordenada y */
	}pointtype;
	//----------------------------------------------------------------------------------------------------
	typedef struct TPonto              /* elemento das tab. pontos */
	{
		short int    endereco;         /* endereco da memoria */
		double x;                      /* coordenada x */
		double y;                      /* coordenada y */
		double z;                      /* coordenada z */
	}TPonto;
	//----------------------------------------------------------------------------------------------------
	typedef struct TFace                    /* elemento da tab. de faces */
	{
		short int np;                       /* num. pontos da face */
		short int cor;                      /* cor da face */
		short int p[MAX_PONTOS_FACE+1];     /* indices dos pontos na tab. de pontos */
	}TFace;
	//----------------------------------------------------------------------------------------------------
	typedef struct TObjeto             /* elemento da tab. objetos */
	{
		short int nf;                  /* num. faces do objeto */
		double escala;                 /* escala do objeto */
		struct TAngulos angulos;       /* angulos atuais do obj. */
		struct TPonto posicao;         /* posicao atual do  obj. */
	}TObjeto;
	//----------------------------------------------------------------------------------------------------
	typedef struct TCor                        /* elemento da tab. cores */
	{
		unsigned char nt;
		short int           endereco;          /* endereco de memoria */
		unsigned char rgb[N_RGB+1];            /* rgb inicial e final */
		unsigned char indice;                  /* indice inicial na paleta */
	}TCor;
}
