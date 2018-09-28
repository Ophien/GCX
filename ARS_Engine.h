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
//#include "GL\glew.h" //para usar as extensões do ogl

#include "ARS_Texture.h"
#include "IL\il.h"
#include "AntTweakBar.h"
#include "CTimer.h"
#include "ARS_Utils.h"
#include "ARS_EventHandler.h"
#include "ARS_Object.h"
#include "ARS_Camera.h"
#include "ARS_Interfaces.h"
#include "ARS_OrthoCam.h"
#include "ARS_Object.h"
#include "ARS_GameObject.h"
#include "ARS_Sprite.h"
#include "ARS_Input.h"
#include "ARS_CameraManager.h"
#include "ARS_WindowInf.h"
#include "ARS_Gui.h"
//#include "GL\glfw.h"

#include "glut.h"

//----------------------------------------------------------------------------------------------------
//using namespace cv;
using namespace ARS_WindowInf;
using namespace ARS_CameraHandler;
using namespace ARS_Input;
//----------------------------------------------------------------------------------------------------
#define ERRO 666
#define GLOBAL_SLEEP_TIME 0
//----------------------------------------------------------------------------------------------------
//int WINDOW_STATE = GLFW_WINDOW;
GLfloat LINE_WIDTH = 1.5f;
#define WINDOW_RED_BITS     8
#define WINDOW_GREEN_BITS   8
#define WINDOW_BLUE_BITS    8
#define WINDOW_ALPHA_BITS   8
#define WINDOW_DEPTH_BITS   8
#define WINDOW_STENCIL_BITS 8
//----------------------------------------------------------------------------------------------------
#define ENABLE_TEXTURE GL_TRUE
//----------------------------------------------------------------------------------------------------
static int WINDOW_WIDTH  = 640;
static int WINDOW_HEIGHT = 480;
static string WINDOW_NAME = "ARSOP Engine - Alysson Ribeiro da Silva OpenGL SPRITE RENDERING ENGINE";
//----------------------------------------------------------------------------------------------------
static int running           = GL_TRUE;
static int NoResize          = GL_FALSE;
static int FSAA_SAMPLES      = 2;
static int refresh_rate      = 60;
//----------------------------------------------------------------------------------------------------
GLfloat global_ambient[]     = {0.0f, 0.0f, 0.0f, 1.0f};
//----------------------------------------------------------------------------------------------------
static int system_keys_enable  = GL_FALSE;
static int key_press_repeat    = GL_TRUE;
static int enable_mouse_cursor = GL_TRUE;
//----------------------------------------------------------------------------------------------------
CTimer _timer;
ARS_MEH*  _mouseEventHandler = ARS_MEH::getInstance();
ARS_MEMH* _mouseMoveEventHandler = ARS_MEMH::getInstance();
ARS_MEWH* _mouseWheelHandler = ARS_MEWH::getInstance();
ARS_KE*   _keyEventHandler = ARS_KE::getInstance();
ARS_KCE*  _keyCharEventHandler = ARS_KCE::getInstance();
ARS_POSUPDATEEH* _posUpdateEventHandler = ARS_POSUPDATEEH::getInstance();
ARS_WINDOW_RESIZEEH* _windowResizeEventHandler = ARS_WINDOW_RESIZEEH::getInstance();
void mDRAW();
//----------------------------------------------------------------------------------------------------
void (*ARS_Update)(double);
void (*ARS_Draw)(double);
//----------------------------------------------------------------------------------------------------
void ARS_SetUpdateFunc(void (*func)(double));
void ARS_SetDrawFunc(void (*func)(double));
//----------------------------------------------------------------------------------------------------
void ARS_Initialize();
void CamConfig();
void ARS_Dispose();
void update();
void mDRAW();
void ARS_Run();
//----------------------------------------------------------------------------------------------------
void TW_CALL CopyStdStringToClient(std::string& destinationClientString, const std::string& sourceLibraryString)
{
  destinationClientString = sourceLibraryString;
}
//----------------------------------------------------------------------------------------------------
void WindowResize(int width, int height){
	TwWindowSize(width, height);

	window.width = width;
	window.height = height;

	CamConfig();

	_windowResizeEventHandler->callAll(width, height);
}
//----------------------------------------------------------------------------------------------------
void ARS_SetUpdateFunc(void (*func)(double)){
	ARS_Update = func;
}
//----------------------------------------------------------------------------------------------------
void ARS_SetDrawFunc(void (*func)(double)){
	ARS_Draw = func;
}
//----------------------------------------------------------------------------------------------------
void mouseClick(int button, int state, int x, int y){
	TwEventMouseButtonGLUT(button, state, x, y);

	mouse._previousButton = mouse._lastButton;
	mouse._previousButtonState = mouse._lastButtonState;

	switch(state){
	case GLUT_UP:
		mouse._lastButtonState = GLUT_UP;
		mouse.buttonPress = false;
		mouse.singleButtonPress = false;
		break;
	case GLUT_DOWN:
		mouse._lastButtonState = GLUT_DOWN;
		mouse.buttonPress = true;
		if(mouse._previousButton != button)
			mouse.singleButtonPress = true;
		else
			mouse.singleButtonPress = false;
		break;
	}

	mouse._lastButton = button;

	_mouseEventHandler->callAll(button, state);
}
//----------------------------------------------------------------------------------------------------
void mousePassiveMotion(int x, int y){
	TwEventMouseMotionGLUT(x,y);

	mouse.pMousePos = mouse.mousePos;
	mouse.mousePos.x = (float)x;
	mouse.mousePos.y = (float)y;

	_mouseMoveEventHandler->callAll(x,y);
}
//----------------------------------------------------------------------------------------------------
void mouseMotion(int x, int y){
	TwEventMouseMotionGLUT(x,y);

	mouse.pMousePos = mouse.mousePos;
	mouse.mousePos.x = (float)x;
	mouse.mousePos.y = (float)y;

	_mouseMoveEventHandler->callAll(x,y);
}
//----------------------------------------------------------------------------------------------------
void keyboardCallBack(unsigned char key, int x, int y){
	TwEventKeyboardGLUT(key, x, y);

	keyboard._previousKey = keyboard._lastKey;
	keyboard._previousKeyState = keyboard._lastKeyState;

	//TODO::COLOCAR EVENTOS AQUI

	keyboard._lastKey = key;

	_keyEventHandler->callAll(key, ARS_pressed);
}
//----------------------------------------------------------------------------------------------------
void configureEvents(){
	glutReshapeFunc(WindowResize);
	glutPassiveMotionFunc(mousePassiveMotion);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseClick);
	glutKeyboardFunc(keyboardCallBack);
	glutDisplayFunc(mDRAW);
	glutIdleFunc(update);
}
//----------------------------------------------------------------------------------------------------
void ARS_Initialize(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(WINDOW_NAME.c_str());
	ilInit();
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	TwCopyStdStringToClientFunc(CopyStdStringToClient);
	TwGLUTModifiersFunc(glutGetModifiers);
	
	//TW helper deactivator
	TwDefine("TW_HELP visible = false");
	
	_timer.Init();

	configureEvents();
	CamConfig();

	if(ENABLE_TEXTURE)
		glEnable(GL_TEXTURE_2D);

	// Funções
	glLineWidth(LINE_WIDTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);		
    
	// Habilitando luz, cull-face e blend
	glEnable(GL_BLEND);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_LINE_SMOOTH);

	/*glEnable(GL_MULTISAMPLE_ARB);
	glEnable(GL_MULTISAMPLE_EXT);
	glEnable(GL_MULTISAMPLE_SGIS);
	glEnable(GL_MULTISAMPLE_3DFX);
	glEnable(GL_MULTISAMPLE_COVERAGE_MODES_NV);
	glEnable(GL_MULTISAMPLE_FILTER_HINT_NV);*/

	// configurando luz ambiente e shadeModel dos pixels
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	//glShadeModel(GL_SMOOTH);

	//glEnable(GL_DEPTH_TEST);    // Enable the depth buffer									
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	
}
//----------------------------------------------------------------------------------------------------
void CamConfig(){
	glViewport( 0, 0, window.width, window.height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(45.0f, (float)window.width / (float)window.height, 0.1f, 10000.0f);
	//glOrtho( 0.0, window.width, window.height, 0, 1.0, -1.0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}
//----------------------------------------------------------------------------------------------------
void ARS_Dispose(){
	TwTerminate();
	//glfwCloseWindow();
	//glfwTerminate();
}
//----------------------------------------------------------------------------------------------------
void update(){
	_timer.Update();
	double _elapsedSeconds = _timer.GetElapsedSeconds();

	ARS_Update(_elapsedSeconds);
	_posUpdateEventHandler->callAll(NULL);

	glutPostRedisplay();
}
//----------------------------------------------------------------------------------------------------
void mDRAW(){
	double _elapsedSeconds = _timer.GetElapsedSeconds();

	glClearColor( clearColor[0], clearColor[1], clearColor[2], 1.f );
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(0,0,-100);
	_camManager.Update(_elapsedSeconds);
	_camManager.updateView();
	ARS_Draw(_elapsedSeconds);
	TwDraw(); 

	glFlush();
	//glFinish();
	//glutSwapBuffers();
}
//----------------------------------------------------------------------------------------------------
void ARS_Run(){
	glutMainLoop();
	//while(true){
	//	mDRAW();
	//}
}
