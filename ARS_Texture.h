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
#include <string>
#include "glut.h"
#include "ARS_Utils.h"

//----------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------
class ARS_Texture{
private:
	GLuint powerOfTwo( GLuint num );
	GLuint _texID;
	GLuint* _texPixels;
	_wh _texWH;

public:
	ARS_Texture(void);
	~ARS_Texture(void);

	GLuint* getPixelData32();
	GLuint getPixel32( GLuint x, GLuint y );
	GLuint getTextureID();
	GLuint textureWidth();
	GLuint textureHeight();
	bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height );
	bool loadTextureFromFile(string path);
	bool lock();
	bool unlock();
	void setPixel32( GLuint x, GLuint y, GLuint pixel );
	void freeTexture();
	_wh _imgWH;
};
