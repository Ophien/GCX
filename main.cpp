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
#include <Windows.h>
#include "ARS_Engine.h"
#include "GCX_Gui.h"
#include "GCX.h"
#include "GCXGLInterface.h"
//----------------------------------------------------------------------------------------------------
using namespace GCX;
using namespace GCX_GUI;
using namespace ARS_GCXInterface;
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
void Draw(double time){
	// Atualiza luz corrente no gcx
	UpdateGCXLight(time);

	// Desenha objetos do gcx
	DrawAllGCXObjects(time);

	// Desenha todo hud do GCX
	GCX_GUI_Draw(time);
}
//----------------------------------------------------------------------------------------------------
void Update(double time){
	// Atualiza gui
	GCX_GUI_Update(time);

	// Roda simulador
	Simulador(time);
}
//----------------------------------------------------------------------------------------------------
int main(int argc, char* argv[]){
	WINDOW_NAME = "GCX NEO"; 
	ARS_Initialize(argc, argv);
	ARS_SetDrawFunc(&Draw);
	ARS_SetUpdateFunc(&Update);

	//printf("%s",argv[1]);

	// Inicializa gui do GCX
	GCX_GUI_init();

	if (argc == 1){ 
		Inicializa("content/bin/defaultCube.exe");
	}
	else{
		Inicializa(argv[1]);
	}

	// args treatment
	for(int i = 2; i < argc; i++){
		if(strcmp(argv[i], "-debug") == 0)
			GCX_DebugTWInit();

		// next arg ...

		// next arg ...
	}

	ARS_Run();

	// Deleta toda gui do GCX
	DisposeAllGui();
	return 0;
}
//----------------------------------------------------------------------------------------------------
