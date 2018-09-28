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
#include "ARS_Sprite.h"
#include "ARS_Input.h"
#include "ARS_Interfaces.h"
#include "ARS_EventHandler.h"
#include "ARS_GameObject.h"
//----------------------------------------------------------------------------------------------------
using namespace ARS_Input;
//----------------------------------------------------------------------------------------------------
typedef enum buttonState{
	ARS_release,
	ARS_pressed,
	ARS_normal,
	ARS_over
}ARS_ButtonState;
//----------------------------------------------------------------------------------------------------
typedef enum textureState{
	ARS_tOver,
	ARS_selected,
	ARS_unselected
}ARS_textureState;
//----------------------------------------------------------------------------------------------------
typedef enum coliderType{
	ARS_hud,
	ARS_world
}ARS_ColType;
//----------------------------------------------------------------------------------------------------
class ARS_Bar{
public:
	ARS_Bar(void){}
	~ARS_Bar(void){}
};
//----------------------------------------------------------------------------------------------------
class ARS_CheckBox{
	ARS_CheckBox(void){}
	~ARS_CheckBox(void){}
};
//----------------------------------------------------------------------------------------------------
class ARS_Colider : public IMouseMoveEvent{
public:
	ARS_Colider(void){
		_col = false;
		ARS_MEMH::getInstance()->registerEvent(this);
	}

	~ARS_Colider(void){
		ARS_MEMH::getInstance()->unregisterEvent(this);
	}

	void init(_wh* whP, ARS_ColType _cal = ARS_hud){
		wh = whP;
		_type = _cal;
	}

	void mouseMoveEvent(int x, int y){
		if(pos==NULL)
			return;

		vec3 _colVec;

		if(_type == ARS_world)
			_colVec = mouse.GetOGLPos((float)x,(float)y);
		else
			_colVec = vec3((float)x, (float)y, 0.0f);

		vec2 val = vec2(_colVec.x, _colVec.y);
		vec3 auxPos = vec3(pos->x, pos->y, pos->z);
		AABB _colPoly = AABB(vec3(0,0,0)+auxPos, vec3((float)wh->width*wh->scale, (float)wh->height*wh->scale,0)+auxPos);
		if(pointInAABB(val, _colPoly)){
			_col = true;
			callOnColision(NULL);
		}
		else{
			_col = false;
			callEndColision(NULL);
		}
	}

	void draw(){
		vec3 auxPos = vec3(pos->x, pos->y, pos->z);
		AABB(vec3(0,0,0)+auxPos,vec3((float)wh->width*wh->scale, (float)wh->height*wh->scale,0)+auxPos).draw();
	}

	void registerColider(IColiderEvent* _event){
		_events.push_back(_event);
	}

	void callOnColision(void* args){
		for(unsigned int i = 0; i < _events.size(); i++)
			_events.at(i)->onColision(args);
	}

	void callEndColision(void* args){
		for(unsigned int i = 0; i < _events.size(); i++)
			_events.at(i)->endColision(args);
	}

	void clearEvents(){
		_events.clear();
	}

	bool col(){return _col;}

	void setPosRef(vec3* _posPtr){
		pos = _posPtr;
	}

private:
	vector<IColiderEvent*> _events;
	vec3 max;
	vec3 min;
	_wh* wh;
	vec3* pos;
	ARS_ColType _type;
	bool _col;
};
//----------------------------------------------------------------------------------------------------
class ARS_Button : public ARS_GameObject, IColiderEvent, IMouseClickEvent{
public:
	bool Enable;

	ARS_Button(void){
	}

	~ARS_Button(void){
		ARS_MEH::getInstance()->unregisterEvent(this);
		if(_texture==0x0)
			return;

		delete _texture;
		_texture = 0x0;
	}

	void init(string texture, _wh wh){
		Enable = true;

		_texture = 0x0;
		_state = ARS_normal;
		_pState = ARS_normal;
		_texture = new ARS_Sprite(texture, wh);
		_texture->setSource(0);
		setScale(wh.scale);

		Source _s = _texture->getSource();
		vec3 max = vec3((float)_s.wh.width, (float)_s.wh.height,0);
		vec3 min = vec3(0,0,0);

		col.init(&_texture->getSourceRef()->wh, ARS_hud);
		col.setPosRef(&position);

		col.registerColider(this);
		ARS_MEH::getInstance()->registerEvent(this);
	}

	void dispose(){
		ARS_MEH::getInstance()->unregisterEvent(this);
		if(_texture == 0x0)
			return;

		delete _texture;
		_texture = 0x0;
	}

	void mouseClickEvent(int button, int state){
				if(!Enable)
			return;

		switch(_state){
		case ARS_normal:
			break;
		case ARS_over:
			if(mouse.buttonPress){//single click
				if(mouse._lastButton == GLUT_LEFT_BUTTON ){
					_pState = _state;
					_state = ARS_pressed;
					_texture->setSource(2);
					pressed();
				}
			}
			break;
		case ARS_pressed:
			if(!mouse.buttonPress){//end click
				if(mouse._lastButton == GLUT_LEFT_BUTTON ){
					_pState = _state;
					_state = ARS_release;//release
					_texture->setSource(1);
					released();
				}
			}
			break;
		case ARS_release:
			if(mouse.buttonPress){//single click
				if(mouse._lastButton == GLUT_LEFT_BUTTON ){
					_pState = _state;
					_state = ARS_pressed;
					_texture->setSource(2);
					pressed();
				}
			}
			break;
		}
	}

	void onColision(void* args){
				if(!Enable)
			return;

		switch(_state){
		case ARS_normal:
			_pState = _state;
			_state = ARS_over;
			_texture->setSource(1);
			over();
			break;
		case ARS_over:
			break;
		case ARS_pressed:
			break;
		case ARS_release:
			break;
		}
	}

	void endColision(void* args){
				if(!Enable)
			return;

		switch(_state){
		case ARS_normal:
			break;
		case ARS_over:
			_pState = _state;
			_state = ARS_normal;
			_texture->setSource(0);
			normal();
			break;
		case ARS_pressed:
			_pState = _state;
			_state = ARS_normal;
			_texture->setSource(0);
			normal();
			break;
		case ARS_release:
			_pState = _state;
			_state = ARS_normal;
			_texture->setSource(0);
			normal();
			break;
		}
	}

	void draw(double _time){
		if(!Enable)
			return;

		_texture->drawSprite(
			position,
			origin,
			scale,
			angleOrigin,
			rotationAngle,
			rotation,
			false);
		col.draw();
	}

	void registerUpdatable(IUpdateEvent* _event){
		_events.push_back(_event);
	}

	void callOnUpdate(void* args){
		if(!Enable)
			return;
		for(unsigned int i = 0; i < _events.size(); i++)
			_events.at(i)->onUpdate(args);
	}

	void clearEvents(){
		_events.clear();
	}

	virtual void pressed()=0;
	virtual void released()=0;
	virtual void normal()=0;
	virtual void over()=0;

private:
	vector<IUpdateEvent*> _events;
	ARS_Colider col;
	ARS_ButtonState _state;
	ARS_ButtonState _pState;
	ARS_Sprite* _texture;
};
//----------------------------------------------------------------------------------------------------
class ARS_textureComp : public ARS_GameObject, IColiderEvent, IMouseClickEvent{
public:
	ARS_textureComp(void){
	}

	~ARS_textureComp(void){
		ARS_MEH::getInstance()->unregisterEvent(this);

		if(_texture==0x0)
			return;

		delete _texture;
		_texture = 0x0;
	}

	void init(string texture, bool* selectable, _wh wh){
		margin = 3;
		_texture = 0x0;
		_state = ARS_unselected;
		_pState = ARS_unselected;
		_texture = new ARS_Sprite(texture, wh);
		_texture->setSource(0);
		selected = false;
		draggable = false;
		mouseOver = false;

		Source _s = _texture->getSource();
		vec3 max = vec3((float)_s.wh.width, (float)_s.wh.height,0);
		vec3 min = vec3(0,0,0);

		col.init(&_texture->getSourceRef()->wh, ARS_world);
		col.setPosRef(&position);

		col.registerColider(this);
		ARS_MEH::getInstance()->registerEvent(this);
	}

	void resetState(){
		_state = ARS_unselected;
		_pState = ARS_unselected;
		selected = false;
		draggable = false;
		mouseOver = false;
	}

	void select(){
		_state = ARS_tOver;
		_pState = ARS_tOver;
		selected = true;
		draggable = false;
		mouseOver = false;
	}

	void init(string texture, bool* selectable){
		margin = 3;
		_texture = 0x0;
		_state = ARS_unselected;
		_pState = ARS_unselected;
		_texture = new ARS_Sprite(texture);
		_texture->setSource(0);
		this->selectable = selectable;
		selected = false;
		draggable = false;
		mouseOver = false;

		Source _s = _texture->getSource();
		vec3 max = vec3((float)_s.wh.width, (float)_s.wh.height,0);
		vec3 min = vec3(0,0,0);

		col.init(&_texture->getSourceRef()->wh, ARS_world);
		col.setPosRef(&position);

		col.registerColider(this);
		ARS_MEH::getInstance()->registerEvent(this);
	}

	void dispose(){
		ARS_MEH::getInstance()->unregisterEvent(this);

		if(_texture == 0x0)
			return;

		delete _texture;
		_texture = 0x0;
	}

	void mouseClickEvent(int button, int state){
		//if(!(*selectable) && !selected )
		//	return;

		switch(_state){
		case ARS_unselected:
			break;
		case ARS_tOver:
			if(!(*selectable))
				return;

			if(!mouseOver)
				return;

			if(keyboard._lastCharKey != 's')
				return;

			if(mouse.buttonPress && 
				button == GLUT_LEFT_BUTTON  &&
				keyboard._lastKeyState == GLUT_DOWN){//single click
					_pState = _state;

					if(selected){
						selected = false;
						//	(*selectable) = true;
						_pState = _state;
						_state = ARS_unselected;
						endSelection();
					}
					else{
						selected = true;
						//	(*selectable) = false;
						onSelection();
					}
			}
			break;
		}
	}

	void onColision(void* args){
		mouseOver = true;
		switch(_state){
		case ARS_unselected:
			_pState = _state;
			_state = ARS_tOver;
			//printf("OVER\n");
			break;
		case ARS_tOver:
			if(selected && !mouse.buttonPress){
				draggable = true;
				over();
			}
			break;
		}
	}

	void endColision(void* args){
		mouseOver = false;
		switch(_state){
		case ARS_unselected:
			break;
		case ARS_tOver:
			_pState = _state;

			if(!selected)
				_state = ARS_unselected;
			else
				draggable = false;

			//printf("OUT\n");
			break;
		}
	}

	void draw(double _time){
		_texture->drawSprite(
			position,
			origin,
			scale,
			angleOrigin,
			rotationAngle,
			rotation,
			false);

		if(selected){
			_wh wh = _texture->getSource().wh;

			float x = position.x;
			float y = position.y;

			glDisable(GL_TEXTURE_2D);

			if(clearColor[0] < 0.30 && clearColor[1] < 0.30 && clearColor[2] < 0.30)
				glColor3f(1,1,1);
			else
				glColor3f(0,0,0);

			glBegin(GL_LINES);
			glVertex3f(0-margin+x,0-margin+y,0);
			glVertex3f(0+margin+(float)wh.width+x,0-margin+y,0);

			glVertex3f(0+(float)wh.width+margin+x,0-margin+y,0);
			glVertex3f(0+(float)wh.width+margin+x,0+(float)wh.height+margin+y,0);

			glVertex3f(0-margin+x,0-margin+y,0);
			glVertex3f(0-margin+x,0+(float)wh.height+margin+y,0);

			glVertex3f(0-margin+x,0+(float)wh.height+margin+y,0);
			glVertex3f(0+(float)wh.width+margin+x,0+(float)wh.height+margin+y,0);
			glEnd();

			glColor3f(1.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
		}

		if(mouseOver){
			_wh wh = _texture->getSource().wh;

			float x = position.x;
			float y = position.y;

			glDisable(GL_TEXTURE_2D);
			glColor4f(1,1,1,0.1f);
			glBegin(GL_QUADS);
			glVertex3f(0+x,0+(float)wh.height+y,0);
			glVertex3f(0+(float)wh.width+x,0+(float)wh.height+y,0);
			glVertex3f(0+(float)wh.width+x,0+y,0);
			glVertex3f(0+x,0+y,0);
			glEnd();
			glColor3f(1.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
		}


		//col.draw();
	}

	void registerUpdatable(IUpdateEvent* _event){
		_events.push_back(_event);
	}

	void callOnUpdate(void* args){
		for(unsigned int i = 0; i < _events.size(); i++)
			_events.at(i)->onUpdate(args);
	}

	void clearEvents(){
		_events.clear();
	}

	virtual void onSelection()=0;
	virtual void endSelection()=0;
	virtual void over()=0;

	ARS_Sprite* getSprite(){
		return _texture;
	}

	void setSelectionMargin(float value){
		margin = value;
	}

	bool isDraggable(){
		return draggable;
	}

	bool isSelected(){
		return selected;
	}

private:
	bool selected;
	bool draggable;
	bool mouseOver;
	vector<IUpdateEvent*> _events;
	ARS_Colider col;
	ARS_textureState _state;
	ARS_textureState _pState;
	ARS_Sprite* _texture;
	float margin;
	bool* selectable;
};
//----------------------------------------------------------------------------------------------------
class ARS_SimpleTexture : public ARS_GameObject{
public:
	bool Enable;

	ARS_SimpleTexture(void){
	}

	~ARS_SimpleTexture(void){
		if(_texture==0x0)
			return;

		delete _texture;
		_texture = 0x0;
	}

	void init(string texture, _wh wh){
		Enable = true;

		_texture = 0x0;
		_texture = new ARS_Sprite(texture, wh);
		_texture->setSource(0);
		setScale(wh.scale);
	}

	void dispose(){
		if(_texture == 0x0)
			return;

		delete _texture;
		_texture = 0x0;
	}

	void draw(double _time){
		if(!Enable)
			return;

		_texture->drawSprite(
			position,
			origin,
			scale,
			angleOrigin,
			rotationAngle,
			rotation,
			false);
	}

	virtual void update(double time)=0;

private:
	ARS_Sprite* _texture;
};
