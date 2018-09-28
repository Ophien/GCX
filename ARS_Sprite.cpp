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
#include "ARS_Sprite.h"
//----------------------------------------------------------------------------------------------------
ARS_Sprite::ARS_Sprite(std::string spriteName){
	_Tex.loadTextureFromFile(spriteName);
	_Source.wh = _Tex._imgWH;
	_Source.pos.x = 0;
	_Source.pos.y = (float)_Tex._imgWH.height;
	startFrame = 0;
	endFrame = 0;
	frameRate = 0;
	currentFrame = 0;
	animRate = 0;
	currentTimer = 0;
	isLoop = true; 
	animationEnd = false;
}
//----------------------------------------------------------------------------------------------------
ARS_Sprite::ARS_Sprite(std::string spriteName, _wh wh)
{
	_Tex.loadTextureFromFile(spriteName);
	_Source.wh = wh;
	_Source.pos.x = 0;
	_Source.pos.y = (float)wh.height;
	startFrame = 0;
	endFrame = 0;
	frameRate = 0;
	currentFrame = 0;
	animRate = 0;
	currentTimer = 0;
	isLoop = true; 
	animationEnd = false;
}
//----------------------------------------------------------------------------------------------------
ARS_Sprite::~ARS_Sprite(void)
{
	_Tex.freeTexture();
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::Dispose(){
}
//----------------------------------------------------------------------------------------------------
ARS_Texture* ARS_Sprite::getTexture(){
	return &_Tex;
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::setSourceWH(_wh wh){
	_Source.wh = wh;
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::setSourcePos(vec2 pos){
	_Source.pos = pos;
}
//----------------------------------------------------------------------------------------------------
float ARS_Sprite::TexToRes(float res, float tex)
{
	return res * tex;
}
//----------------------------------------------------------------------------------------------------
float ARS_Sprite::ResToTexWidth(float res)
{
	return res / _Tex._imgWH.width;
}
//----------------------------------------------------------------------------------------------------
float ARS_Sprite::ResToTexHeight(float res)
{
	return res / _Tex._imgWH.height;
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::setFrames(int start, int end){
	startFrame = start;
	endFrame = end;
	currentFrame = start;
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::setAnimRate(int frames){
	if (frames > 0 && animRate == 0)
		activate();
	animRate = 1.0f / frames;//fps
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::activate(){
	currentFrame = 0;
	currentTimer = 0.0f;
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::setLoop(){
	if (isLoop)
		isLoop = false;   
	else
	{
		isLoop = true;
		activate();
	}
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::calcSourcePosition()
{
	float x = float(_Source.pos.x);
	float y = float(_Source.pos.y);
	float sH = float(_Source.wh.height+_Source.pos.y);
	float sW = float(_Source.wh.width+_Source.pos.x);
	_Source.x = ResToTexWidth(x);
	_Source.y = ResToTexHeight(y);
	_Source.x1 = _Source.x;
	_Source.y1 = ResToTexHeight(sH);// - ResToTexHeight(sourceHeight);
	_Source.x2 = ResToTexWidth(sW);
	_Source.y2 = _Source.y;// - ResToTexHeight(sourceHeight);
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::setSource(int frame){
	int countWidth = 1;
	int xIndex = 0;
	int yIndex = 0;

	if(_Source.wh.width == 0)
		return;

	if(_Source.wh.width <= _Tex._imgWH.width)
		countWidth = _Tex._imgWH.width / _Source.wh.width;
	
	xIndex = frame % countWidth;
	yIndex = frame / countWidth;
	vec2 sPos = vec2((float)_Source.wh.width * (float)xIndex, (float)_Source.wh.height * (float)yIndex);

	setSourcePos(sPos);
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::update(double time){
	currentTimer += time;
	if (currentTimer > animRate)
	{
		currentTimer -= animRate;
		if (currentFrame < endFrame-1)
			currentFrame++;
		else if (isLoop)
		{
			currentFrame = startFrame;
			animationEnd = true;
		}
	}
	setSource(currentFrame);
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::drawSprite(
	vec3& position, 
	vec3& origin, 
	float scale,
	vec3& angleOrigin,
	vec3& rotationAngle,
	vec3& rotation, 
	bool fliped){
		glPushMatrix();
		doAllTrasnformations(position, origin, scale, angleOrigin, rotationAngle, rotation);
		GLfloat w = GLfloat(_Source.wh.width);
		GLfloat h = GLfloat(_Source.wh.height);
		glScalef(w,h,0);
		glBindTexture(GL_TEXTURE_2D, _Tex.getTextureID());
		calcSourcePosition();

		if(!fliped)
			texMap();
		else
			flipedTexMap();

		glPopMatrix();
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::texMap()
{
	glBegin(GL_QUADS);
	glTexCoord2f(_Source.x1, _Source.y2); glVertex3f(0.0f, 0.0f,  0.0f);
	glTexCoord2f(_Source.x1, _Source.y1); glVertex3f(0.0f, 1.0f,  0.0f);
	glTexCoord2f(_Source.x2, _Source.y1); glVertex3f(1.0f, 1.0f,  0.0f);
	glTexCoord2f(_Source.x2, _Source.y2); glVertex3f(1.0f, 0.0f,  0.0f);
	glEnd();
}
//----------------------------------------------------------------------------------------------------
void ARS_Sprite::flipedTexMap()
{
	glBegin(GL_QUADS);
	glTexCoord2f(_Source.x2, _Source.y2); glVertex3f(0.0f, 0.0f,  0.0f);
	glTexCoord2f(_Source.x2, _Source.y1); glVertex3f(0.0f, 1.0f,  0.0f);
	glTexCoord2f(_Source.x1, _Source.y1); glVertex3f(1.0f, 1.0f,  0.0f);
	glTexCoord2f(_Source.x1, _Source.y2); glVertex3f(1.0f, 0.0f,  0.0f);
	glEnd();	
}
