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
#include "ARS_Texture.h"
#include "ARS_Utils.h"
#include "ARS_Object.h"
#include "ARS_Utils.h"
#include <string>
//----------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------
class ARS_Sprite : public ARS_Object
{
public:
	ARS_Sprite(std::string spriteName, _wh wh);
	ARS_Sprite(std::string spriteName);
	~ARS_Sprite(void);

	void Initizalie(std::string spriteName);
	void Dispose();
	ARS_Texture* getTexture();
	void setSourceWH(_wh wh);
	void setSourcePos(vec2 pos);
	void drawSprite(
		vec3& position, 
		vec3& origin, 
		float scale,
		vec3& angleOrigin,
		vec3& rotationAngle,
		vec3& rotation, 
		bool fliped);
	void setFrames(int start, int end);
	void setAnimRate(int frames);
	void activate();
	void setLoop();
	void setSource(int frame);
	float TexToRes(float res, float tex);
	float ResToTexWidth(float res);
	float ResToTexHeight(float res);
	void calcSourcePosition();
	void update(double time);
	void texMap();
	void flipedTexMap();
	Source getSource(){return _Source;}
	Source* getSourceRef(){return &_Source;}
	double* getAnimRateRef(){return &animRate;}
	double* getCurrentTimerRef(){return &currentTimer;}
	int* getStartFrameRef(){return &startFrame;}
	int* getEndFrameRef(){return &endFrame;}
	int* getFrameRateRef(){return &frameRate;}
	int* getCurrentFrameRef(){return &currentFrame;}

private:
	ARS_Texture _Tex;
	Source _Source;

	//frame controll
	int startFrame, endFrame, frameRate, currentFrame;
	double animRate, currentTimer;
	bool isLoop, animationEnd;
};

