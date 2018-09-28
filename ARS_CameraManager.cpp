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
#include "ARS_CameraManager.h"
#include "ARS_EventHandler.h"
//----------------------------------------------------------------------------------------------------
namespace ARS_CameraHandler{
	ARS_CameraManager _camManager;
}
//----------------------------------------------------------------------------------------------------
ARS_CameraManager::ARS_CameraManager(void)
{
	ARS_PerspectiveCam* newCam = new ARS_PerspectiveCam();
	newCam->setPosition_Z(800);
	newCam->setPosition_Y(-30);
	newCam->init(45, 0.001f, 10000.0f);
	newCam->setControls('W','S','A','D');
	cameras.push_back(newCam);
	currentCamera = 0;

	ARS_MEMH::getInstance()->registerEvent(this);
	ARS_MEWH::getInstance()->registerEvent(this);
	ARS_MEH::getInstance()->registerEvent(this);
}
//----------------------------------------------------------------------------------------------------
ARS_CameraManager::~ARS_CameraManager(void)
{
	ARS_MEMH::getInstance()->unregisterEvent(this);
	ARS_MEWH::getInstance()->unregisterEvent(this);
	ARS_MEH::getInstance()->unregisterEvent(this);

	for(unsigned int i = 0; i < cameras.size(); i++){
		delete cameras.at(i);
		cameras.at(i) = 0x0;
	}
}
//----------------------------------------------------------------------------------------------------
int ARS_CameraManager::incrementCam(){
	int prev = currentCamera;
	if(currentCamera + 1 == cameras.size())
		currentCamera = 0;
	return prev;
}
//----------------------------------------------------------------------------------------------------
int ARS_CameraManager::decrementCam(){
	int prev = currentCamera;
	if(currentCamera - 1 < 0)
		currentCamera = cameras.size() - 1;
	return prev;
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::insertCam(ARS_Camera* cam)
{
	cameras.push_back(cam);
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::removeCam()
{
	if(cameras.size() == 1)
		exit(-1);

	cameras.pop_back();
}
//----------------------------------------------------------------------------------------------------
ARS_Camera* ARS_CameraManager::getCurrent()
{
	return cameras.at(currentCamera);
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::updateCamera()
{
	cameras.at(currentCamera)->update();
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::updateView()
{
	cameras.at(currentCamera)->updateView();
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::mouseClickEvent(int button, int state){
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::mouseMoveEvent(int x, int y){
	cameras.at(currentCamera)->move();
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::mouseWheelEvent(int WheeValue){
	cameras.at(currentCamera)->update();
}
//----------------------------------------------------------------------------------------------------
void ARS_CameraManager::Update(double time){
	cameras.at(currentCamera)->update(time);
}
//----------------------------------------------------------------------------------------------------
