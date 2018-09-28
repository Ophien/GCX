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
#include <windows.h>
#include <dos.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#include <stack>
//----------------------------------------------------------------------------------------------------
#include "GCXConfig.h"
#include "GCXObjects.h"
#include "ARS_Light.h"
//----------------------------------------------------------------------------------------------------
void TW_CALL GotoInstruction(void* clientData){
	
}
//----------------------------------------------------------------------------------------------------
using namespace std;
using namespace GCX_OBJECTS;
using namespace GCX_CONFIG;
//----------------------------------------------------------------------------------------------------
namespace GCX{
	char* fileName;
	//----------------------------------------------------------------------------------------------------
	typedef struct TPonto TLuz;
	//----------------------------------------------------------------------------------------------------
	short int 
		n_pontos,                  /* numero de pontos ja definidos */
		n_faces,                   /* numero de faces ja definidas */
		n_objetos,                 /* numero de objetos ja definidos */
		n_cores,                   /* numero de cores ja definidas */
		n_luzes,                   /* numero de luzes ja definidas */
		n_simbolos,                /**/
		n_linhas,                  /* N. linhas compiladas */
		obj_cor,                   /* objeto e luz correntes */
		luz_cor;
	//----------------------------------------------------------------------------------------------------
	unsigned char n_paleta;        /* primeira entrada livre da paleta */ // TODO::remover
	FILE *arq = NULL;                     /* arquivo fonte */
	//----------------------------------------------------------------------------------------------------
	// Para controlar a luz na interface de comunicação
	ARS_Light _CurrentLight;
	bool   useSleep    = true;
	double sleepFactor = 1000;
	//----------------------------------------------------------------------------------------------------
	TAngulos DAngulos;            /* DeltaAngulos de Rotacao */
	TPonto   DPosicao;            /* Deltas de deslocamento */
	TPonto   TPO[MAX_PONTOS+1];   /* tab. pontos originais */
	TPonto   TP3[MAX_PONTOS+1];   /* tab. pontos 3D transformados*/
	TFace    TF[MAX_FACES+1];     /* tab. faces */
	TCor     TC[MAX_CORES+1];     /* tab. cores */
	TObjeto  TB;                  /* tab. objetos */
	TPonto   TL;                  /* tab. luzes */
	//----------------------------------------------------------------------------------------------------
	short  int MD[MAXMEMORIA],MC[MAXMEMORIA]; /* memoria de dados/codigo */
	short  int PC;                            /* Primeiro end. vazio codigo */
	short  int Regs[NREGS+1];                 /* registradores inteiros */
	double     RegsF[NREGS+1];                /* registradores reais */
	float      SleepTime = -1.0f;
	//----------------------------------------------------------------------------------------------------
	// Time walk controll
	typedef struct TimeCell{
		// Time cell controle do simulador
		short  int MD[MAXMEMORIA]; /* memoria de dados/codigo */
		short  int PC;                            /* Primeiro end. vazio codigo */
		short  int Regs[NREGS+1];                 /* registradores inteiros */
		double     RegsF[NREGS+1];                /* registradores reais */
		float      SleepTime;

		// Time cell controle de variáveis
		TAngulos DAngulos;            /* DeltaAngulos de Rotacao */
		TPonto   DPosicao;            /* Deltas de deslocamento */
		TPonto   TPO[MAX_PONTOS+1];   /* tab. pontos originais */
		TPonto   TP3[MAX_PONTOS+1];   /* tab. pontos 3D transformados*/
		TFace    TF[MAX_FACES+1];     /* tab. faces */
		TCor     TC[MAX_CORES+1];     /* tab. cores */
		TObjeto  TB;                  /* tab. objetos */
		TPonto   TL;                  /* tab. luzes */

		// Time cell current lightning
		ARS_Light _CurrentLight;

		short int 
			n_pontos,                  /* numero de pontos ja definidos */
			n_faces,                   /* numero de faces ja definidas */
			n_objetos,                 /* numero de objetos ja definidos */
			n_cores,                   /* numero de cores ja definidas */
			n_luzes,                   /* numero de luzes ja definidas */
			n_simbolos,                /**/
			n_linhas,                  /* N. linhas compiladas */
			obj_cor,                   /* objeto e luz correntes */
			luz_cor;

		bool EndExecution;
	}TimeCell;
	//----------------------------------------------------------------------------------------------------
	// Manipuladores de tempo
	void CreateTimeCell();
	void RewindTime();
	void OneStep();
	void TimeWalk();
	bool EnablePerStep();
	//----------------------------------------------------------------------------------------------------
	// TIME WALK CONTROLL VARIABLES
	int  StepsToExecute          = 0;
	bool PerStep                 = true;
	bool EnableIterationTracking = true;
	bool EndExecution            = false;
	stack<TimeCell>              _TimeStack;
	stack<int>                   _InstructionStack;
	//----------------------------------------------------------------------------------------------------
	void CreateTimeCell(){
		TimeCell _Cell;

		_Cell.DAngulos = DAngulos;
		_Cell.DPosicao = DPosicao;
		_Cell.luz_cor  = luz_cor;

		// Copiando memoria de código
		for(int i = 0; i < MAXMEMORIA; i++)
			_Cell.MD[i] = MD[i];

		_Cell.PC = PC;

		// Copiando conteúdo dos registradores
		for(int i = 0; i < NREGS+1; i++){
			_Cell.Regs[i]  = Regs[i];
			_Cell.RegsF[i] = RegsF[i];
		}

		_Cell.SleepTime = SleepTime;

		// Copiando conteúdo das faces e objetos
		for(int i = 0; i < MAX_PONTOS+1; i++){
			_Cell.TPO[i] = TPO[i];
			_Cell.TP3[i] = TP3[i];
		}

		// Copiando tab de faces
		for(int i = 0; i < MAX_FACES + 1; i++)
			_Cell.TF[i] = TF[i];

		// Copiando tab de cores
		for(int i = 0; i < MAX_CORES + 1; i++)
			_Cell.TC[i] = TC[i];

		// Copiando objeto atual
		_Cell.TB = TB;

		_Cell.TL = TL;

		_Cell._CurrentLight = _CurrentLight;

		_Cell.n_pontos   = n_pontos;                  
		_Cell.n_faces    = n_faces;          
		_Cell.n_objetos  = n_objetos;                 
		_Cell.n_cores    = n_cores;                   
		_Cell.n_luzes    = n_luzes;                   
		_Cell.n_simbolos = n_simbolos;               
		_Cell.n_linhas   = n_linhas;                  
		_Cell.obj_cor    = obj_cor;                
		_Cell.luz_cor    = luz_cor;

		_Cell.EndExecution = EndExecution;

		_TimeStack.push(_Cell);
	}
	//----------------------------------------------------------------------------------------------------
	void RewindTime(){
		TimeCell _Cell = _TimeStack.top();
		_TimeStack.pop();

		DAngulos = _Cell.DAngulos;
		DPosicao = _Cell.DPosicao;
		luz_cor  = _Cell.luz_cor;

		// Copiando memoria de código
		for(int i = 0; i < MAXMEMORIA; i++)
			MD[i] = _Cell.MD[i];

		PC = _Cell.PC;

		// Copiando conteúdo dos registradores
		for(int i = 0; i < NREGS+1; i++){
			Regs[i]  = _Cell.Regs[i]; 
			RegsF[i] = _Cell.RegsF[i];
		}

		SleepTime = _Cell.SleepTime;

		// Copiando conteúdo das faces e objetos
		for(int i = 0; i < MAX_PONTOS+1; i++){
			TPO[i] = _Cell.TPO[i];
			TP3[i] = _Cell.TP3[i];
		}

		// Copiando tab de faces
		for(int i = 0; i < MAX_FACES + 1; i++)
			TF[i] = _Cell.TF[i];

		// Copiando tab de cores
		for(int i = 0; i < MAX_CORES + 1; i++)
			TC[i] =_Cell.TC[i];

		// Copiando objeto atual
		TB = _Cell.TB;

		TL = _Cell.TL;

		n_pontos   = _Cell.n_pontos;                  
		n_faces    = _Cell.n_faces;          
		n_objetos  = _Cell.n_objetos;                 
		n_cores    = _Cell.n_cores;                   
		n_luzes    = _Cell.n_luzes;                   
		n_simbolos = _Cell.n_simbolos;               
		n_linhas   = _Cell.n_linhas;                  
		obj_cor    = _Cell.obj_cor;                
		luz_cor    = _Cell.luz_cor;

		// Configura luz
		if(_Cell.luz_cor == -1)
			_CurrentLight.TurnOff();

		_CurrentLight = _Cell._CurrentLight;

		EndExecution = _Cell.EndExecution;
	}
	//----------------------------------------------------------------------------------------------------
	void OneStep(){
		if(PerStep)
			StepsToExecute+=1;
	}
	//----------------------------------------------------------------------------------------------------
	void TimeWalk(){
		if(_TimeStack.size() <= 0)
			return;

		if(PerStep){
			RewindTime();
			_InstructionStack.pop();
		}
	}
	//----------------------------------------------------------------------------------------------------
	bool EnablePerStep(){
		if(PerStep)
			PerStep = false;
		else
			PerStep = true;

		return PerStep;
	}
	// TIME WALK CONTROLL
	//----------------------------------------------------------------------------------------------------
	void Finaliza(char *s)

		/*----------------------------------------------------------------------*/
		/*   Termina a execucao do programa, retornando ao modo texto e         */
		/*   exibindo uma mensagem.                                             */
		/*----------------------------------------------------------------------*/

	{
		//TODO::COLOCAR CÓDIGO
		EndExecution = true;
	}
	//----------------------------------------------------------------------------------------------------
	double ValorReal(short int *M, short int posicao)
	{
		/*
		{----------------------------------------------------------------------}
		{   Retorna real armazenado na memoria.                                }
		{----------------------------------------------------------------------}
		*/
		return((double)M[posicao]+(double)M[posicao+1]/10000.0); // =P
	}
	//----------------------------------------------------------------------------------------------------
	inline short int EscolheCor(double coseno, short int cor)

		/*----------------------------------------------------------------------*/
		/*   Escolhe um tom de cor, a partir do coseno entre a normal e a       */
		/*   fonte de luz.                                                      */
		/*----------------------------------------------------------------------*/

	{
		return(TC[cor].indice+(short int)(coseno*(TC[cor].nt-1)));
	}
	//----------------------------------------------------------------------------------------------------
	void DefineAngulos(double a, double b, double g, struct TAngulos & ang)

		/*----------------------------------------------------------------------*/
		/*   Define o registro ang, a partir dos valores a,b,g e calcula os     */
		/*   senos e cosenos.                                                   */
		/*----------------------------------------------------------------------*/

	{
		ang.alfa = a;
		ang.beta = b;
		ang.gama = g;
		ang.ca = cos(ang.alfa);
		ang.sa = sin(ang.alfa);
		ang.cb = cos(ang.beta);
		ang.sb = sin(ang.beta);
		ang.cg = cos(ang.gama);
		ang.sg = sin(ang.gama);
	}
	//----------------------------------------------------------------------------------------------------
	void DefinePosicao(double x, double y, double z, struct TPonto & p)

		/*----------------------------------------------------------------------*/
		/*   Define o registro p (ponto) a partir das coordenadas x,y,z.        */
		/*----------------------------------------------------------------------*/

	{
		p.x = x;
		p.y = y;
		p.z = z;
	}
	//----------------------------------------------------------------------------------------------------
	inline double Modulo(struct TPonto v)

		/*----------------------------------------------------------------------*/
		/*   Calcula o modulo de um vetor.                                      */
		/*----------------------------------------------------------------------*/

	{
		return(sqrt(v.x*v.x + v.y*v.y + v.z*v.z));
	}
	//----------------------------------------------------------------------------------------------------
	inline void Unitario(struct TPonto & v)

		/*----------------------------------------------------------------------*/
		/*   Transforma um vetor em um vetor unitario.                          */
		/*----------------------------------------------------------------------*/

	{
		double modulo_aux;

		modulo_aux = Modulo(v);
		v.x /= modulo_aux;
		v.y /= modulo_aux;
		v.z /= modulo_aux;
	}
	//----------------------------------------------------------------------------------------------------
	void DeterminaNormal(struct TFace f, struct TPonto & n)

		/*-----------------------------------------------------------*/
		/*   Calcula a normal de um poligono, no ponto 2.            */
		/*-----------------------------------------------------------*/

	{
		n.x = (TP3[f.p[3]].y-TP3[f.p[2]].y)*(TP3[f.p[1]].z-TP3[f.p[2]].z) -
			(TP3[f.p[3]].z-TP3[f.p[2]].z)*(TP3[f.p[1]].y-TP3[f.p[2]].y);
		n.y = (TP3[f.p[3]].z-TP3[f.p[2]].z)*(TP3[f.p[1]].x-TP3[f.p[2]].x) -
			(TP3[f.p[3]].x-TP3[f.p[2]].x)*(TP3[f.p[1]].z-TP3[f.p[2]].z);
		n.z = (TP3[f.p[3]].x-TP3[f.p[2]].x)*(TP3[f.p[1]].y-TP3[f.p[2]].y) -
			(TP3[f.p[3]].y-TP3[f.p[2]].y)*(TP3[f.p[1]].x-TP3[f.p[2]].x);
		Unitario(n);
	}
	//----------------------------------------------------------------------------------------------------
	inline void CalculaVetor(struct TPonto p1, struct TPonto p2, struct TPonto & v)

		/*----------------------------------------------------------------------*/
		/*   Determina o vetor de P1 a P2.                                      */
		/*----------------------------------------------------------------------*/

	{
		v.x = p2.x-p1.x;
		v.y = p2.y-p1.y;
		v.z = p2.z-p1.z;
		Unitario(v);
	}
	//----------------------------------------------------------------------------------------------------
	inline double CosenoAngulo(struct TPonto n, struct TPonto q)

		/*----------------------------------------------------------------------*/
		/*   Calcula o coseno do angulo entre dois vetores.                     */
		/*----------------------------------------------------------------------*/

	{
		return(n.x*q.x + n.y*q.y + n.z*q.z);
	}
	//----------------------------------------------------------------------------------------------------
	inline void Escalar(struct TPonto p1, struct TPonto & p2, double escala)

		/*----------------------------------------------------------------------*/
		/*   Escala as coordenadas de um ponto.                                 */
		/*----------------------------------------------------------------------*/

	{
		p2.x = p1.x*escala;
		p2.y = p1.y*escala;
		p2.z = p1.z*escala;
	}
	//----------------------------------------------------------------------------------------------------
	inline void Translacao(struct TPonto p1, struct TPonto & p2, struct TPonto v)

		/*----------------------------------------------------------------------*/
		/*   Calcula em p2 o resultado da translacao de p1 por um vetor V.      */
		/*----------------------------------------------------------------------*/

	{
		p2.x = p1.x+v.x;
		p2.y = p1.y+v.y;
		p2.z = p1.z+v.z;
	}
	//----------------------------------------------------------------------------------------------------
	inline void Rotacao(struct TPonto p1, struct TPonto & p2, struct TAngulos a)

		/*----------------------------------------------------------------------*/
		/*   Calcula em p2 o resultado da rotacao de p1 por delta-angulos a.    */
		/*----------------------------------------------------------------------*/

	{
		double xi,yi,zi;

		xi = p1.x*a.ca - p1.y*a.sa;
		yi = p1.x*a.sa + p1.y*a.ca;
		zi = p1.z*a.cb + yi*a.sb;
		p2.y = yi*a.cb - p1.z*a.sb;
		p2.z = zi*a.cg - xi*a.sg;
		p2.x = zi*a.sg + xi*a.cg;

		//TODO::Esses calculos abaixo estão com problemas

		//p2.z = ((-1 * a.sb * a.cg)                   * p1.x) + (( a.sb * a.sg )                   * p1.y) + (( a.cb )      * p1.z);
		//p2.y = (( a.sa * a.cb * a.cg + a.ca * a.sg ) * p1.x) + (( -1*a.ca*a.cb*a.sg + a.ca*a.cg ) * p1.y) + (( a.sa*a.sb ) * p1.z);
		//p2.x = (( a.ca *a.cb *a.cg - a.sa*a.sg )     * p1.x) + ((-1*a.ca *a.cb*a.sg-a.sa*a.cg)    * p1.y) + (( a.ca*a.sb ) * p1.z);
	}
	//----------------------------------------------------------------------------------------------------
	// Essa função é chamada apenas 1 vez e é controlada dentro de um loop :-)
	void RotacaoTranslacao(struct TAngulos a, struct TPonto d)

		/*----------------------------------------------------------------------*/
		/*   Executa, em animacao de N passos, a rotacao por A delta-angulos e  */
		/*   a translacao de D delta-coordenadas de um Objeto iluminado por Luz.*/
		/*----------------------------------------------------------------------*/

	{
		short int i,j;
		double c_aux;                       /* cosseno auxiliar */

		int transladar,rotacionar;          /* Var. para selecao de funcao */

		/* Determina se havera rot/trans. */
		rotacionar=((a.alfa!=0.0) || (a.beta!=0.0) || (a.gama!=0.0))?1:0;
		transladar=((d.x!=0.0) || (d.y!=0.0) || (d.z!=0.0))?1:0;

		//TB = Objeto atual da cena
		// Translada
		if (transladar)
		{
			TB.posicao.x+=d.x;
			TB.posicao.y+=d.y;
			TB.posicao.z+=d.z;
		}

		// Calcula angulos de rotação
		if (rotacionar)
		{
			// Incrementa 
			TB.angulos.alfa += a.alfa;
			TB.angulos.beta += a.beta;
			TB.angulos.gama += a.gama;

			// Deve ser colocado aqui para recalcular os senos e os cossenos
			// todas vez que alterar o valor
			// Calcular novo seno e cosseno
			TB.angulos.ca = cos(TB.angulos.alfa);
			TB.angulos.sa = sin(TB.angulos.alfa);

			TB.angulos.cb = cos(TB.angulos.beta);
			TB.angulos.sb = sin(TB.angulos.beta);

			TB.angulos.cg = cos(TB.angulos.gama);
			TB.angulos.sg = sin(TB.angulos.gama);
			// Calcular novo seno e cosseno

			// Calcula novos coeficientes de rotação para dar algum efeito
			c_aux = TB.angulos.ca;

			TB.angulos.ca = TB.angulos.ca*a.ca - TB.angulos.sa*a.sa; // novo cos alpha
			TB.angulos.sa = c_aux*a.sa         + a.ca*TB.angulos.sa; // novo sin alpha

			c_aux = TB.angulos.cb;

			TB.angulos.cb = TB.angulos.cb*a.cb - TB.angulos.sb*a.sb; // novo cos beta
			TB.angulos.sb = c_aux*a.sb         + a.cb*TB.angulos.sb; // novo sin beta

			c_aux = TB.angulos.cg;

			TB.angulos.cg = TB.angulos.cg*a.cg - TB.angulos.sg*a.sg; // novo cos gama
			TB.angulos.sg = c_aux*a.sg         + a.cg*TB.angulos.sg; // novo sin gama
			// Calcula novos coeficientes de rotação para dar algum efeito
		}

		// Transforma cada vertice do objeto
		for (i=1; i<=TB.nf; i++){// Aplica transformações em cada face
			for (j=1; j<=TF[i].np; j++)//percorre pontos da face
			{
				Escalar(TPO[TF[i].p[j]],    TP3[TF[i].p[j]], TB.escala);

				// TODO::DEBUG PRINT
				//printf("alpha %f beta %f gama %f\n", TB.angulos.alfa, TB.angulos.beta, TB.angulos.gama);

				Rotacao(TP3[TF[i].p[j]],    TP3[TF[i].p[j]], TB.angulos);
				Translacao(TP3[TF[i].p[j]], TP3[TF[i].p[j]], TB.posicao);
			}
		}
	}
	//----------------------------------------------------------------------------------------------------
	short int CarregaPonto(short int posicao)
	{
		/*
		{----------------------------------------------------------------------}
		{   Insere Ponto da posicao de memoria na tabela de pontos, caso nao   }
		{   tenha sido inserida. Retorna o indice da tabela onde foi inserida. }
		{----------------------------------------------------------------------}
		*/
		short int i;

		i=1;
		while (i<= n_pontos && TPO[i].endereco!=posicao) i++;
		if (i>n_pontos)
		{
			if (n_pontos<MAX_PONTOS)
			{
				n_pontos++;
				TPO[n_pontos].endereco=posicao;
				TPO[n_pontos].x=ValorReal(MD,posicao);
				TPO[n_pontos].y=ValorReal(MD,posicao+2);
				TPO[n_pontos].z=ValorReal(MD,posicao+4);
				return(n_pontos);
			} else Finaliza("ERRO! Tabela de pontos esta cheia.");
		} else return(i);
		return(0);
	}
	//----------------------------------------------------------------------------------------------------
	short int CarregaCor(short int posicao)
	{
		/*
		{----------------------------------------------------------------------}
		{   Insere Cor da posicao de memoria na tabela de cores, caso nao      }
		{   tenha sido inserida. Retorna o indice da tabela onde foi inserida. }
		{   Calcula tons.                                                      }
		{----------------------------------------------------------------------}
		*/
		short int i;

		i=1;
		while (i<= n_cores && TC[i].endereco!=posicao) i++;
		if (i>n_cores)
		{
			if (n_cores<MAXCOR)// && n_paleta+MD[posicao]<=getmaxcolor())
			{
				n_cores++;
				TC[n_cores].endereco=posicao;
				TC[n_cores].nt=MD[posicao];
				for (i=1; i<=6; i++) TC[n_cores].rgb[i]=MD[posicao+i];
				TC[n_cores].indice=n_paleta+1;

				// ESSE FOR É DESNECESSÁRIO
				/*for (i=0; i<=TC[n_cores].nt-1; i++)
				{
				//setrgbpalette(TC[n_cores].indice+i,
				//(int)(TC[n_cores].rgb[1]+(TC[n_cores].rgb[4]-TC[n_cores].rgb[1])*i/
				//TC[n_cores].nt),
				//(int)(TC[n_cores].rgb[2]+(TC[n_cores].rgb[5]-TC[n_cores].rgb[2])*i/
				//TC[n_cores].nt),
				//(int)(TC[n_cores].rgb[3]+(TC[n_cores].rgb[6]-TC[n_cores].rgb[3])*i/
				//TC[n_cores].nt));

				//setpalette(TC[n_cores].indice+i,TC[n_cores].indice+i);
				}*/
				n_paleta+=TC[n_cores].nt;
				return(n_cores);
			} else Finaliza("ERRO! Tabela de cores esta cheia.");
		} else return(i);
		return(0);
	}
	//----------------------------------------------------------------------------------------------------
	void CarregaFace(short int n, short int posicao)
	{
		short int i;
		/*
		{----------------------------------------------------------------------}
		{   Carrega Face numero n da posicao de memoria na tabela de faces.    }
		{----------------------------------------------------------------------}
		*/
		TF[n].np=MD[posicao];
		TF[n].cor=CarregaCor(MD[posicao+1]);
		if (TF[n].np <= MAX_PONTOS_FACE)
			for (i=1; i<=TF[n].np; i++)
				TF[n].p[i]=CarregaPonto(MD[posicao+i+1]);
		else Finaliza("ERRO! Numero maximo de pontos por face foi ultrapassado.");
	}
	//----------------------------------------------------------------------------------------------------
	void CarregaLuz(short int posicao)
	{
		/*
		{----------------------------------------------------------------------}
		{   Carrega luz da posicao de memoria como luz corrente.               }
		{----------------------------------------------------------------------}
		*/
		// Desliga luz antiga
		_CurrentLight.TurnOff();

		luz_cor=posicao;
		TL.x=ValorReal(MD,luz_cor);
		TL.y=ValorReal(MD,luz_cor+2);
		TL.z=ValorReal(MD,luz_cor+4);

		// Atualiza posição de luz
		_CurrentLight.setPosition(TL.x, TL.y, TL.z);

		// Liga nova luz
		_CurrentLight.TurnOn();
	}
	//----------------------------------------------------------------------------------------------------
	void CarregaObjeto(short int posicao)
	{
		short int i;
		/*
		{----------------------------------------------------------------------}
		{   Carrega objeto da posicao de memoria como obj. corrente            }
		{----------------------------------------------------------------------}
		*/

		obj_cor=posicao;//?
		TB.nf=MD[obj_cor];//?
		TB.escala=ValorReal(MD,obj_cor+1);//?
		for (i=1; i<=TB.nf; i++)
			if (i<MAX_FACES_OBJETO) CarregaFace(i,MD[obj_cor+2+i]);
			else Finaliza("ERRO! Numero maximo de faces por objeto foi ultrapassado.");

			//Tive que tirar......... -________-
			//DefinePosicao(0,0,0,TB.posicao);// faz perder transformação anterior................. -___-
			//DefineAngulos(0,0,0,TB.angulos);// fez perder rotação anterior....................... -___-
	}
	//----------------------------------------------------------------------------------------------------
	void Simulador(double _time)
	{
		if(EndExecution)
			return;

		bool disableSleep = false;

		if(useSleep){
			if(SleepTime <= 0){
				SleepTime = 0;
			}else{
				SleepTime -= (float)(_time);
				return;
			}
		}

		// Controle de fluxo de dados
		if(PerStep){
			if(StepsToExecute<=0)
				return;
		}

		// Controle de time walking
		if(EnableIterationTracking){
			CreateTimeCell();// Cria celula de tempo da itera��o atual
			_InstructionStack.push(MC[PC]);
		}
	
		/*
		{----------------------------------------------------------------------}
		{   Simula a maquina GL.                                               }
		{----------------------------------------------------------------------}
		*/
		//printf("Instrução %i\n", MC[PC]);
		switch (MC[PC])
		{
		case ADD:
			Regs[MC[PC+1]]=Regs[MC[PC+1]]+Regs[MC[PC+2]];
			PC+=3;
			break;
		case ADDF:
			RegsF[MC[PC+1]]=RegsF[MC[PC+1]]+RegsF[MC[PC+2]];
			PC+=3;
			break;
		case ADI:
			Regs[MC[PC+1]]=Regs[MC[PC+1]]+MC[PC+2];
			PC+=3;
			break;
		case ADIF:
			RegsF[MC[PC+1]]=RegsF[MC[PC+1]]+ValorReal(MC,PC+2);
			PC+=4;
			break;
		case BNG:
			if (Regs[MC[PC+1]]<0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BNGF:
			if (RegsF[MC[PC+1]]<0.0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BNN:
			if (Regs[MC[PC+1]]>=0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BNNF:
			if (RegsF[MC[PC+1]]>=0.0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BNP:
			if (Regs[MC[PC+1]]<=0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BNPF:
			if (RegsF[MC[PC+1]]<=0.0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BNZ:
			if (Regs[MC[PC+1]]!=0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BNZF:
			if (RegsF[MC[PC+1]]!=0.0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BPS:
			if (Regs[MC[PC+1]]>0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BPSF:
			if (RegsF[MC[PC+1]]>0.0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BZR:
			if (Regs[MC[PC+1]]==0) PC=MC[PC+2];
			else PC+=3;
			break;
		case BZRF:
			if (RegsF[MC[PC+1]]==0.0) PC=MC[PC+2];
			else PC+=3;
			break;
		case CNV:
			RegsF[MC[PC+1]]=Regs[MC[PC+2]];
			PC+=3;
			break;
		case DVD:
			RegsF[MC[PC+1]]=RegsF[MC[PC+1]]/RegsF[MC[PC+2]];
			PC+=3;
			break;
		case ESC:
			MD[Regs[MC[PC+1]]+1]=(short int)(RegsF[MC[PC+2]]);
			MD[Regs[MC[PC+1]]+2]=(short int)(10000*
				(RegsF[MC[PC+2]]-(double)((short int)(RegsF[MC[PC+2]]))));
			TB.escala=RegsF[MC[PC+2]];
			PC+=3;
			break;
		case HLT:Finaliza(""); break;
		case JMP:PC=MC[PC+1]; break;
		case LDI:
			Regs[MC[PC+1]]=MC[PC+2];
			PC+=3;
			break;
		case LDIF:
			RegsF[MC[PC+1]]=ValorReal(MC,PC+2);
			PC+=4;
			break;
		case LGT:
			if (Regs[MC[PC+1]]!=luz_cor) CarregaLuz(Regs[MC[PC+1]]);
			PC+=2;
			break;
		case LOD:
			Regs[MC[PC+1]]=MD[MC[PC+2]];
			PC+=3;
			break;
		case LODF:
			RegsF[MC[PC+1]]=ValorReal(MD,MC[PC+2]);
			PC+=3;
			break;
		case MOV:
			Regs[MC[PC+1]]=Regs[MC[PC+2]];
			PC+=3;
			break;
		case MOVF:
			RegsF[MC[PC+1]]=RegsF[MC[PC+2]];
			PC+=3;
			break;
		case MUL:
			Regs[MC[PC+1]]=Regs[MC[PC+1]]*Regs[MC[PC+2]];
			PC+=3;
			break;
		case MULF:
			RegsF[MC[PC+1]]=RegsF[MC[PC+1]]*RegsF[MC[PC+2]];
			PC+=3;
			break;
		case NEG:
			Regs[MC[PC+1]]=-Regs[MC[PC+1]];
			PC+=2;
			break;
		case NEGF:
			RegsF[MC[PC+1]]=-RegsF[MC[PC+1]];
			PC+=2;
			break;
		case RTR:
			/*if (Regs[A]!=obj_cor)*/ 
			CarregaObjeto(Regs[A]);
			DefineAngulos(RegsF[A],RegsF[B],RegsF[C],DAngulos);
			DefinePosicao(RegsF[D],RegsF[E],RegsF[F],DPosicao);

			// Aqui aparenta estar correto
			//printf("ANGULOS: %f %f %f        TRANSLATE: %f %f %f\n", RegsF[A],RegsF[B],RegsF[C],RegsF[D],RegsF[E],RegsF[F]);
			//system("pause");			

			RotacaoTranslacao(DAngulos,DPosicao);
			//printf("Instrução %i\n", MC[PC]);
			PC++;
			break;
		case STI:
			MD[MC[PC+2]]=MC[PC+1];
			PC+=3;
			break;
		case STIF:
			MD[MC[PC+3]]=MC[PC+1];
			MD[MC[PC+3]+1]=MC[PC+2];
			PC+=4;
			break;
		case STO:
			MD[MC[PC+2]]=Regs[MC[PC+1]];
			PC+=3;
			break;
		case STOF:
			MD[MC[PC+2]]=(short int)(RegsF[MC[PC+1]]);
			MD[MC[PC+2]+1]=(short int)(10000*
				(RegsF[MC[PC+1]]-(double)((short int)(RegsF[MC[PC+1]]))));
			PC+=3;
			break;
		case SUB:
			Regs[MC[PC+1]]=Regs[MC[PC+1]]-Regs[MC[PC+2]];
			PC+=3;
			break;
		case SUBF:
			RegsF[MC[PC+1]]=RegsF[MC[PC+1]]-RegsF[MC[PC+2]];
			PC+=3;
			break;
		case TME:
			//TODO::verificar novo sleep
			SleepTime = (float)(RegsF[MC[PC+1]])/sleepFactor;
			PC+=2;
			break;
		}

		// Controle de fluxo de dados
		if(PerStep){
			if(StepsToExecute > 0){
				StepsToExecute--;
			}
		}
	}
	//----------------------------------------------------------------------------------------------------
	void RewindAllTime(){
		while(_TimeStack.size() > 0){
			RewindTime();
		}
	}
	//----------------------------------------------------------------------------------------------------
	void Inicializa(char *fname){
		char DEFAULT_DIRECTORY[10000] = "content/bin/";
		strcat_s(DEFAULT_DIRECTORY, 10000, fname);

		//Control variables
		short int i;//,posicao,palavra;
		short int tamanho, lidos;
		struct stat statrec;

		lidos = 0;
		arq;

		//File name
		fileName = fname;

		//File reading 
		stat(fname,&statrec);
		tamanho = statrec.st_size/sizeof(short);
		int err = fopen_s(&arq, fname, "rb");

		if (err!=0) {
			fileName = DEFAULT_DIRECTORY;
			stat(DEFAULT_DIRECTORY,&statrec);
			tamanho  = statrec.st_size/sizeof(short);
			err      = fopen_s(&arq, DEFAULT_DIRECTORY, "rb");
		}

		if (err!=0) {printf("File not found !!!\nPress any key to continue...\n"); getchar(); exit(err);};
		if (tamanho>MAXMEMORIA) {printf("Memory overflow !!!\nPress any key to continue...\n"); getchar(); exit(-1);}
		lidos=fread((void *)(MC),sizeof(short),tamanho,arq);

		if (lidos!=tamanho) {printf("File size erro !!!\nPress any key to continue...\n"); getchar(); exit(-1);};
		fclose(arq);

		// Simulator preparation
		PC        = 0;
		n_pontos  = 0;
		n_faces   = 0;
		n_objetos = 0;
		n_cores   = 0;
		n_luzes   = 0;
		n_paleta  = 0;
		luz_cor   =-1;
		obj_cor   =-1;

		// Zera tabela de pontos e cores
		for (i=1; i<=MAX_PONTOS; i++) TPO[i].endereco=-1;
		for (i=1; i<=MAX_CORES; i++)  TC[i].endereco =-1;
	}
	
}// FIM NAMESPACE
