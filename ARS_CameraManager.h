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
#include <vector>
#include "ARS_Camera.h"
#include "ARS_OrthoCam.h"
#include "ARS_PerspectiveCam.h"
#include "ARS_Interfaces.h"
//----------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------
class ARS_CameraManager : public IMouseClickEvent, IMouseWheelEvent, IMouseMoveEvent
{
public:
	ARS_CameraManager(void);
	~ARS_CameraManager(void);

	void insertCam(ARS_Camera* cam);
	void removeCam();
	ARS_Camera* getCurrent();
	void updateCamera();
	void Update(double time);
	void updateView();
	int incrementCam();
	int decrementCam();

	void mouseClickEvent(int button, int state);
	void mouseMoveEvent(int x, int y);
	void mouseWheelEvent(int WheeValue);

private:
	vector<ARS_Camera*> cameras;
	int currentCamera;
};
//----------------------------------------------------------------------------------------------------
namespace ARS_CameraHandler{
	extern ARS_CameraManager _camManager;
}



