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
#include <list>
#include "ARS_Interfaces.h"
//----------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------
class ARS_MEH{
public:
	static ARS_MEH* getInstance(){
		static ARS_MEH instance;
		return &instance;
	}

	ARS_MEH(){}

	~ARS_MEH(){

	}

	void registerEvent(IMouseClickEvent* _event){
		_events.push_back(_event);
		printf("MOUSE CLICK EVENT REGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void callAll(int button, int state){
		list<IMouseClickEvent*>::iterator it = _events.begin();
		for(;it!=_events.end();it++){
			//printf("MOUSE CLICK EVENT CALL - OBJ: 0x%u PARAM: 0x%u \n", this, _events.at(i));
			(*it)->mouseClickEvent(button, state);
		}
	}

	void unregisterEvent(IMouseClickEvent* _event){
		_events.remove(_event);
		printf("MOUSE CLICK EVENT UNREGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void clear(){
		_events.clear();
	}

private:
	list<IMouseClickEvent*> _events;
};
//----------------------------------------------------------------------------------------------------
class ARS_MEMH{
private:
	list<IMouseMoveEvent*> _events;

public:
	static ARS_MEMH* getInstance(){
		static ARS_MEMH instance;
		return &instance;
	}

	ARS_MEMH(){
		//printf("Constructor\n");
	}

	ARS_MEMH(const ARS_MEMH& v){
		//printf("Copy constructor...\n");
	}

	void operator= (const ARS_MEMH& v) {
		//printf("Copy operator...\n");
	}

	~ARS_MEMH(){
		//printf("destructor\n");
	}

	void registerEvent(IMouseMoveEvent* _event){
		_events.push_back(_event);
		printf("MOUSE MOVE EVENT REGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);

		//for(unsigned int i = 0; i < _events.size(); i++){
		//printf("   obj %u : 0x%x \n", i , _events[i] );
		//}
	}

	void unregisterEvent(IMouseMoveEvent* _event){
		_events.remove(_event);
		printf("MOUSE MOVE EVENT UNREGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);

		//for(unsigned int i = 0; i < _events.size(); i++){
		//printf("   obj %u : 0x%x \n", i , _events[i] );
		//}
	}

	void callAll(int x, int y){
		//printf("MOUSE MOVE EVENT CALL - OBJ: 0x%x \n",this);
		list<IMouseMoveEvent*>::iterator it = _events.begin();
		for(;it!=_events.end();it++){
			//printf("MOUSE MOVE EVENT CALL - OBJ: 0x%x PARAM: 0x%x \n", this, _events.at(i));
			(*it)->mouseMoveEvent(x, y);
		}
	}

	void clear(){
		//printf("Clear");
		_events.clear();
	}
};
//----------------------------------------------------------------------------------------------------
class ARS_MEWH{
public:
	static ARS_MEWH* getInstance(){
		static ARS_MEWH instance;
		return &instance;
	}

	ARS_MEWH(){}

	~ARS_MEWH(){}

	void registerEvent(IMouseWheelEvent* _event){
		_events.push_back(_event);
		printf("MOUSE WHEEL EVENT REGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void callAll(int WheeValue){
		list<IMouseWheelEvent*>::iterator it = _events.begin();
		for(;it!=_events.end();it++){
			//printf("MOUSE WHEEL EVENT CALL - OBJ: 0x%u PARAM: 0x%u \n", this, _events.at(i));
			(*it)->mouseWheelEvent(WheeValue);
		}
	}

	void unregisterEvent(IMouseWheelEvent* _event){
		_events.remove(_event);
		printf("MOUSE WHEEL EVENT UNREGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void clear(){
		_events.clear();
	}

private:
	list<IMouseWheelEvent*> _events;
};
//----------------------------------------------------------------------------------------------------
class ARS_KE{
public:
	static ARS_KE* getInstance(){
		static ARS_KE instance;
		return &instance;
	}

	ARS_KE(){}

	~ARS_KE(){}

	void registerEvent(IKeyEvent* _event){
		_events.push_back(_event);
		printf("KEYBOARD EVENT REGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void callAll(int key, int state){
		list<IKeyEvent*>::iterator it = _events.begin();
		for(;it!=_events.end();it++){
			(*it)->keyEvent(key, state);
		}
	}

	void unregisterEvent(IKeyEvent* _event){
		_events.remove(_event);
		printf("KEYBOARD EVENT UNREGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void clear(){
		_events.clear();
	}

private:
	list<IKeyEvent*> _events;
};
//----------------------------------------------------------------------------------------------------
class ARS_KCE{
public:
	static ARS_KCE* getInstance(){
		static ARS_KCE instance;
		return &instance;
	}

	ARS_KCE(){}

	~ARS_KCE(){}

	void registerEvent(IKeyCharEvent* _event){
		_events.push_back(_event);
		printf("KEYBOARD CHAR EVENT REGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void callAll(int key, int state){
		list<IKeyCharEvent*>::iterator it = _events.begin();
		for(;it!=_events.end();it++){
			(*it)->keyCharEvent(key, state);
		}
	}

	void unregisterEvent(IKeyCharEvent* _event){
		_events.remove(_event);
		printf("KEYBOARD CHAR EVENT REGISTERED  - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void clear(){
		_events.clear();
	}

private:
	list<IKeyCharEvent*> _events;
};
//----------------------------------------------------------------------------------------------------
class ARS_POSUPDATEEH{
public:
	static ARS_POSUPDATEEH* getInstance(){
		static ARS_POSUPDATEEH instance;
		return &instance;
	}

	ARS_POSUPDATEEH(){}

	~ARS_POSUPDATEEH(){}

	void registerEvent(IPosUpdateEvent* _event){
		_events.push_back(_event);
		printf("POS UPDATE EVENT REGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void callAll(void* args){
		list<IPosUpdateEvent*>::iterator it = _events.begin();
		for(;it!=_events.end();it++){
			(*it)->posUpdate(args);
		}
	}

	void unregisterEvent(IPosUpdateEvent* _event){
		_events.remove(_event);
		printf("POS UPDATE EVENT UNREGISTERED  - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void clear(){
		_events.clear();
	}

private:
	list<IPosUpdateEvent*> _events;
};
//----------------------------------------------------------------------------------------------------
class ARS_WINDOW_RESIZEEH{
public:
	static ARS_WINDOW_RESIZEEH* getInstance(){
		static ARS_WINDOW_RESIZEEH instance;
		return &instance;
	}

	ARS_WINDOW_RESIZEEH(){}

	~ARS_WINDOW_RESIZEEH(){}

	void registerEvent(IWindowResize* _event){
		_events.push_back(_event);
		printf("WINDOW RESIZE EVENT REGISTERED - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void callAll(int width, int height){
		list<IWindowResize*>::iterator it = _events.begin();
		for(;it!=_events.end();it++){
			(*it)->windowResize(width, height);
		}
	}

	void unregisterEvent(IWindowResize* _event){
		_events.remove(_event);
		printf("WINDOW RESIZE EVENT UNREGISTERED  - OBJ: 0x%x PARAM: 0x%x \n", this, _event);
	}

	void clear(){
		_events.clear();
	}

private:
	list<IWindowResize*> _events;
};
