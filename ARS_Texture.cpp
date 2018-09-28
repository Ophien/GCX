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
#include <stdio.h>
#include "IL\il.h"
#include "ARS_Texture.h"
//----------------------------------------------------------------------------------------------------
ARS_Texture::ARS_Texture(void){
	_texID = 0;
	_texPixels = NULL;
}
//----------------------------------------------------------------------------------------------------
ARS_Texture::~ARS_Texture(void){
	freeTexture();
}
//----------------------------------------------------------------------------------------------------
bool ARS_Texture::loadTextureFromFile(string path){
	bool textureLoaded = false;

	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage( imgID );
	ILboolean success = ilLoadImage( path.c_str() );

	if(success == IL_TRUE){
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);//para ter certeza q está em RGBA
		if(success == IL_TRUE){
			 textureLoaded = loadTextureFromPixels32( 
				 (GLuint*)ilGetData(), 
				 (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), 
				 (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ) );
		}
		 ilDeleteImages( 1, &imgID );
	}

	if(!textureLoaded){
		printf("Unable to load %s\n", path.c_str());
	}

	return textureLoaded;
}
//----------------------------------------------------------------------------------------------------
bool ARS_Texture::loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height ){
	freeTexture();
	_texWH.width = width;
	_texWH.height = height;
	_imgWH = _texWH;
	glGenTextures(1, &_texID);//gera id para textura
	glBindTexture( GL_TEXTURE_2D, _texID);//carrega textura 
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );//gera textura na q foi carregada
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );//carrega parametros da textura
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );//carrega parametros da textura
	glBindTexture( GL_TEXTURE_2D, NULL );//tira textura da memoria para n renderizar nd com ela

	GLenum error = glGetError();//verifica se houve algum erro nas operações
	if( error != GL_NO_ERROR )
	{
		printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
		return false;
	}

	return true;
}
//----------------------------------------------------------------------------------------------------
void ARS_Texture::freeTexture(){
	//Delete texture
	if( _texID != 0 )
	{
		glDeleteTextures( 1, &_texID );
		_texID = 0;
	}

	//Delete pixels
	if( _texPixels != NULL )
	{
		delete[] _texPixels;
		_texPixels = NULL;
	}
}
//----------------------------------------------------------------------------------------------------
bool ARS_Texture::lock()
{
	if( _texPixels == NULL && _texID != 0 )
	{
		GLuint size = _texWH.width * _texWH.height;
		_texPixels = new GLuint[ size ];
		glBindTexture( GL_TEXTURE_2D, _texID );//coloca imagem na placa de video
		glGetTexImage( GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texPixels );//pega imagem e passa para o vetor
		glBindTexture( GL_TEXTURE_2D, NULL );//desaloca imagem da placa de video

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------------------------------
bool ARS_Texture::unlock()
{
	if( _texPixels != NULL && _texID != 0 )
	{
		glBindTexture( GL_TEXTURE_2D, _texID );
		glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, _texWH.width, _texWH.height, GL_RGBA, GL_UNSIGNED_BYTE, _texPixels );
		delete[] _texPixels;
		_texPixels = NULL;
		glBindTexture( GL_TEXTURE_2D, NULL );

		return true;
	}

	return false;
}
//----------------------------------------------------------------------------------------------------
GLuint* ARS_Texture::getPixelData32()
{
	return _texPixels;
}
//----------------------------------------------------------------------------------------------------
GLuint ARS_Texture::getPixel32( GLuint x, GLuint y )
{
	return _texPixels[ y * _texWH.width + x ];
}
//----------------------------------------------------------------------------------------------------
void ARS_Texture::setPixel32( GLuint x, GLuint y, GLuint pixel )
{
	_texPixels[ y * _texWH.width + x ] = pixel;
}
//----------------------------------------------------------------------------------------------------
GLuint ARS_Texture::textureWidth()
{
    return _texWH.width;
}
//----------------------------------------------------------------------------------------------------
GLuint ARS_Texture::textureHeight()
{
	return _texWH.height;
}
//----------------------------------------------------------------------------------------------------
GLuint ARS_Texture::getTextureID(){
	return _texID;
}
