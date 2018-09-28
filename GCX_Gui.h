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
#include "ARS_Gui.h"
#include "ARS_WindowInf.h"
#include "GCX.h"
//----------------------------------------------------------------------------------------------------
using namespace GCX;
using namespace ARS_WindowInf;
//----------------------------------------------------------------------------------------------------
#define ARS_CLOSE   0
#define ARS_RESTART 1
//----------------------------------------------------------------------------------------------------
namespace GCX_GUI{
	//----------------------------------------------------------------------------------------------------
	//void DEBUG_GET_CURRENT_INSTRUCTION();
	void changeStopPlayButton();
	void GCX_GUI_init();
	void GCX_GUI_Draw();
	void ConfigureGuiPosition();
	void WindowResizeMenu();

	void drawText(string s, int x, int y){
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);		

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0.0, window.width, 0.0, window.height);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		glClear(GL_DEPTH_BUFFER_BIT);
		glColor3f(1.0, 1.0, 1.0); 
		glColor3f(1.0, 1.0, 1.0); 
		glRasterPos2i(x, y);
		void * font = GLUT_BITMAP_9_BY_15;
		for (string::iterator i = s.begin(); i != s.end(); ++i)
		{

			char c = *i;
			glutBitmapCharacter(font, c);
		}
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		glEnable(GL_BLEND);
		glEnable(GL_LIGHTING);
		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
	}

	//----------------------------------------------------------------------------------------------------
	void DEBUG_PRINT_CURRENT_TIME_STEP();
	char* DEBUG_GET_CURRENT_INSTRUCTION();
	//----------------------------------------------------------------------------------------------------
	class SimpleRect : public ARS_GameObject, public ARS_Object{
	public:
		SimpleRect(int width, int height, vec3 color){this->width = width; this->height = height; this->color = color;drawBorder=true;}
		~SimpleRect(void){}
		int width;
		int height;
		vec3 color;
		bool drawBorder;
		void draw(){
			glDisable(GL_TEXTURE_2D);
			glPushMatrix();
			doAllTrasnformations(position, origin, scale, angleOrigin, rotationAngle, rotation);
			glScalef((float)width, (float)height, 1);
			glBegin(GL_QUADS);
			glColor3f(color.x,color.y,color.z);
			glVertex3f(0,0,0.0);
			glColor3f(color.x,color.y,color.z);
			glVertex3f(0,1,0.0);
			glColor3f(color.x,color.y,color.z);
			glVertex3f(1,1,0.0);
			glColor3f(color.x,color.y,color.z);
			glVertex3f(1,0,0.0);
			glColor3f(1,1,1);
			glEnd();
			glPopMatrix();
			glEnable(GL_TEXTURE_2D);	
		}
	private:
	};
	//----------------------------------------------------------------------------------------------------
	class NEXT_ITERATION : public ARS_Button{

	public:
		void pressed(){
			DEBUG_PRINT_CURRENT_TIME_STEP();//TODO::DEBUG PRINT
			OneStep();
		}
		void released(){}
		void normal(){}
		void over(){}
	};
	//----------------------------------------------------------------------------------------------------
	class PREV_ITERATION : public ARS_Button{

	public:
		void pressed(){
			DEBUG_PRINT_CURRENT_TIME_STEP();//TODO::DEBUG PRINT
			TimeWalk();
		}
		void released(){}
		void normal(){}
		void over(){}
	};
	//----------------------------------------------------------------------------------------------------
	class PLAY : public ARS_Button{

	public:
		void pressed(){
			EnablePerStep();
			changeStopPlayButton();
		}
		void released(){}
		void normal(){}
		void over(){}
	};
	//----------------------------------------------------------------------------------------------------
	class STOP : public ARS_Button{

	public:
		void pressed(){
			EnablePerStep();
			changeStopPlayButton();
		}
		void released(){}
		void normal(){}
		void over(){}
	};
	//----------------------------------------------------------------------------------------------------
	class EXEC : public ARS_SimpleTexture{
		float rotFactor;
	public:
		EXEC(void){
			rotFactor = 20.0f;
		}
		void update(double time){
			rotateZ(rotFactor*time, 1);
		}
	};
	//----------------------------------------------------------------------------------------------------
	class GCXWindowResizeGUI : public IWindowResize{
	public:
		GCXWindowResizeGUI(void){
			_windowResizeEventHandler->registerEvent(this);
		}
		~GCXWindowResizeGUI(void){
			_windowResizeEventHandler->unregisterEvent(this);
		}

		void windowResize(int width, int height){
			ConfigureGuiPosition();
		}
	};
	//----------------------------------------------------------------------------------------------------
	// Buttons
	NEXT_ITERATION* _Next;
	PREV_ITERATION* _Prev;
	PLAY*           _Cont;
	STOP*           _Stop;
	SimpleRect*     _RECT;
	SimpleRect*     _STRIP_RECT;
	unsigned int	GlobalMenu;
	//----------------------------------------------------------------------------------------------------
	// Gui sprites
	EXEC*           _exec;
	//----------------------------------------------------------------------------------------------------
	// Global gui config
	float _GlobalScale             = 0.3f;
	float _RotSpriteScale          = 0.2f;
	float _ButtonMargin            = 22.0f;
	vec3  _IterationButtonPosition = vec3(50,0,0);
	vec3  _ExeSpritePosition       = vec3(50,0,0);
	GCXWindowResizeGUI*            _ResizeEvent;
	//----------------------------------------------------------------------------------------------------
	// TW bars
	TwBar *debugBar;
	//----------------------------------------------------------------------------------------------------
	void changeStopPlayButton(){
		if(PerStep){
			_Cont->Enable = true;
			_Stop->Enable = false;
		}else{
			_Cont->Enable = false;
			_Stop->Enable = true;
		}
	}
	//----------------------------------------------------------------------------------------------------
	void processMenuEvents(int entry){
		switch(entry){
		case ARS_RESTART:
			RewindAllTime();
			break;
		case ARS_CLOSE:
			exit(0);
			break;
		}
	}
	//----------------------------------------------------------------------------------------------------
	void ConfigureGuiPosition(){
		// Buttons config
		float _relativeXposition = window.width / 2 - ((128 * 3 + _ButtonMargin * 2 ) * _GlobalScale) / 2;
		float _relativeYposition = window.height - (128 + _ButtonMargin) * _GlobalScale;

		_IterationButtonPosition.x = _relativeXposition;
		_IterationButtonPosition.y = _relativeYposition;

		_Prev->setPosition(_IterationButtonPosition.x, _IterationButtonPosition.y, _IterationButtonPosition.z);
		_Next->setPosition(_IterationButtonPosition.x, _IterationButtonPosition.y, _IterationButtonPosition.z);
		_Next->increment_X((128*2+_ButtonMargin*2) * _GlobalScale);
		_Cont->setPosition(_IterationButtonPosition.x, _IterationButtonPosition.y, _IterationButtonPosition.z);
		_Cont->increment_X((128 + _ButtonMargin) *_GlobalScale);
		_Stop->setPosition(_IterationButtonPosition.x, _IterationButtonPosition.y, _IterationButtonPosition.z);
		_Stop->increment_X((128 + _ButtonMargin) *_GlobalScale);

		// Sprites config
		_relativeXposition   = window.width - (128 / 2  + _ButtonMargin) * _RotSpriteScale;
		_relativeYposition   = window.height - (128 / 2 + _ButtonMargin) * _RotSpriteScale;
		_ExeSpritePosition.x = _relativeXposition;
		_ExeSpritePosition.y = _relativeYposition;

		_exec->setPosition(_ExeSpritePosition.x, _ExeSpritePosition.y, _ExeSpritePosition.z);
		_exec->setOrigin(-1 * 128 * _RotSpriteScale / 2, -1 * 128 * _RotSpriteScale / 2, 0);

		//FONTES

		//BARRA 
		_RECT->width = window.width;
		_RECT->setPosition(0, window.height - _RECT->height, 0);
		_STRIP_RECT->width = window.width;
		_STRIP_RECT->setPosition(0,window.height - _RECT->height,0);

		//GLUT GU

		// create the menu and
		// tell glut that "processMenuEvents" will
		// handle the events
		GlobalMenu = glutCreateMenu(processMenuEvents);

		//add entries to our menu
		glutAddMenuEntry("Restart",ARS_RESTART);
		glutAddMenuEntry("Close"  ,ARS_CLOSE);

		// attach the menu to the right button
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	//----------------------------------------------------------------------------------------------------
	void GCX_GUI_init(){		
		// Configura bot\F5es debaixo e alinha com tamanho da janela
		_Prev = new PREV_ITERATION();
		_Prev->init("content/textures/prevButton.png", _wh(128,128,_GlobalScale));

		_Next = new NEXT_ITERATION();
		_Next->init("content/textures/nextButton.png", _wh(128,128,_GlobalScale));

		_Cont = new PLAY();
		_Cont->init("content/textures/playButton.png", _wh(128,128,_GlobalScale));

		_Stop = new STOP();
		_Stop->init("content/textures/stopButton.png", _wh(128,128,_GlobalScale));

		_exec = new EXEC();
		_exec->init("content/textures/execution.png", _wh(128,128,_RotSpriteScale));

		_RECT       = new SimpleRect(1280, 60, vec3(0,0,0));
		_STRIP_RECT = new SimpleRect(1280, 1 , vec3(1,1,1));

		changeStopPlayButton();

		// Configurando posi\E7\E3o inicial
		ConfigureGuiPosition();

		// Configurando evento de resize
		_ResizeEvent = new GCXWindowResizeGUI();
	}
	//----------------------------------------------------------------------------------------------------
	void GCX_DebugTWInit(){
		debugBar = TwNewBar("Debug");

		TwAddSeparator(debugBar, "int"  , "group=Integer" );
		TwAddSeparator(debugBar, "doub" , "group=Double"  );
		TwAddSeparator(debugBar, "Ot"   , "group=Other"   );
		  
		//PC COUNTER
		TwAddVarRO(debugBar, "PC", TwType::TW_TYPE_INT16, &GCX::PC, "group=Other");

		//Integer regs
		TwAddVarRW(debugBar, "A", TwType::TW_TYPE_INT16, &GCX::Regs[1], "group=Integer");
		TwAddVarRW(debugBar, "B", TwType::TW_TYPE_INT16, &GCX::Regs[2], "group=Integer");
		TwAddVarRW(debugBar, "C", TwType::TW_TYPE_INT16, &GCX::Regs[3], "group=Integer");
		TwAddVarRW(debugBar, "D", TwType::TW_TYPE_INT16, &GCX::Regs[4], "group=Integer");
		TwAddVarRW(debugBar, "E", TwType::TW_TYPE_INT16, &GCX::Regs[5], "group=Integer");
		TwAddVarRW(debugBar, "F", TwType::TW_TYPE_INT16, &GCX::Regs[6], "group=Integer");
		
		//Float regs
		TwAddVarRW(debugBar, "Af", TwType::TW_TYPE_DOUBLE, &GCX::RegsF[1], "group=Double");
		TwAddVarRW(debugBar, "Bf", TwType::TW_TYPE_DOUBLE, &GCX::RegsF[2], "group=Double");
		TwAddVarRW(debugBar, "Cf", TwType::TW_TYPE_DOUBLE, &GCX::RegsF[3], "group=Double");
		TwAddVarRW(debugBar, "Df", TwType::TW_TYPE_DOUBLE, &GCX::RegsF[4], "group=Double");
		TwAddVarRW(debugBar, "Ef", TwType::TW_TYPE_DOUBLE, &GCX::RegsF[5], "group=Double");
		TwAddVarRW(debugBar, "Ff", TwType::TW_TYPE_DOUBLE, &GCX::RegsF[6], "group=Double");

		TwDefine("Debug refresh=0 size='200 330' resizable=false");
	}
	//----------------------------------------------------------------------------------------------------
	void DisposeAllGui(){
		if(_Prev!=NULL){
			delete _Prev;
			_Prev = NULL;
		}
		if(_Next!=NULL){
			delete _Next;
			_Next = NULL;
		}
		if(_Cont!=NULL){
			delete _Cont;
			_Cont = NULL;
		}
		if(_Stop!=NULL){
			delete _Stop;
			_Stop = NULL;
		}
		if(_ResizeEvent!=NULL){
			delete _ResizeEvent;
			_ResizeEvent = NULL;
		}
	}
	//----------------------------------------------------------------------------------------------------
	void GCX_GUI_Draw(double time){
		ARS_HudBegin();
		_RECT->draw();
		_STRIP_RECT->draw();
		_Next->draw(time);
		_Prev->draw(time);
		_Cont->draw(time);
		_Stop->draw(time);
		_exec->draw(time);
		ARS_HudEnd();

		//glClear(GL_DEPTH_BUFFER_BIT);
		char buf[100];
		sprintf_s(buf,"Next inst. :%s", DEBUG_GET_CURRENT_INSTRUCTION());
		drawText(buf, 20, 40);
		//sprintf_s(buf, "A: %i",	Regs[A]);
		//drawText(buf, 20, 10);
		//glEnable(GL_BLEND);
		//glEnable(GL_LINE_SMOOTH);

		//DEBUG_PRINT_CURRENT_TIME_STEP();
	}
	//----------------------------------------------------------------------------------------------------
	void GCX_GUI_Update(double time){
		_exec->update(time);
	}
	//----------------------------------------------------------------------------------------------------
	void DEBUG_PRINT_CURRENT_TIME_STEP(){
		printf("--------------------------------------------\n");
		printf("Last instruction: %s\n", DEBUG_GET_CURRENT_INSTRUCTION());
		printf("Last PC: %i\n", PC);
		printf("Last int registers values: \n");
		printf("A - %i\nB - %i\nC - %i\nD - %i\nE - %i\nF - %i\n", 
			Regs[A], Regs[B], Regs[C], Regs[D], Regs[E], Regs[F]);
		printf("Last float registers values: \n");
		printf("Af - %f\nBf - %f\nCf - %f\nDf - %f\nEf - %f\nFf - %f\n", 
			RegsF[A], RegsF[B], RegsF[C], RegsF[D], RegsF[E], Regs[F]);
		printf("--------------------------------------------\n");
	}
	//----------------------------------------------------------------------------------------------------
	char* DEBUG_GET_CURRENT_INSTRUCTION(){
		switch (MC[PC])
		{
		case ADD:
			return "ADD";
			break;
		case ADDF:
			return "ADDF";
			break;
		case ADI:
			return "ADI";
			break;
		case ADIF:
			return "ADIF";
			break;
		case BNG:
			return "BNG";
			break;
		case BNGF:
			return "BNGF";
			break;
		case BNN:
			return "BNN";
			break;
		case BNNF:
			return "BNNF";
			break;
		case BNP:
			return "BNP";
			break;
		case BNPF:
			return "BNPF";
			break;
		case BNZ:
			return "BNZ";
			break;
		case BNZF:
			return "BNZF";
			break;
		case BPS:
			return "BPS";
			break;
		case BPSF:
			return "BPSF";
			break;
		case BZR:
			return "BZR";
			break;
		case BZRF:
			return "BZRF";
			break;
		case CNV:
			return "CNV";
			break;
		case DVD:
			return "DVD";
			break;
		case ESC:
			return "ESC";
			break;
		case HLT:return "HLT"; break;
		case JMP:return "JMP"; break;
		case LDI:
			return "LDI";
			break;
		case LDIF:
			return "LDIF";
			break;
		case LGT:
			return "LGT";
			break;
		case LOD:
			return "LOD";
			break;
		case LODF:
			return "LODF";
			break;
		case MOV:
			return "MOV";
			break;
		case MOVF:
			return "MOVF";
			break;
		case MUL:
			return "MUL";
			break;
		case MULF:
			return "MULF";
			break;
		case NEG:
			return "NEG";
			break;
		case NEGF:
			return "NEGF";
			break;
		case RTR:
			return "RTR";
			break;
		case STI:
			return "STI";
			break;
		case STIF:
			return "STIF";
			break;
		case STO:
			return "STO";
			break;
		case STOF:
			return "STOF";
			break;
		case SUB:
			return "SUB";
			break;
		case SUBF:
			return "SUBF";
			break;
		case TME:
			return "TME";
			break;
		}

		//Caso n\E3o caia em nenhum caso
		return "";
	}//Fim fun\E7\E3o para imprimir

}
