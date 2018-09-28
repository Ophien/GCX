#ifndef vec2_h
#define vec2_h

#include <string.h>

#ifdef vec2_h_COMPILING


#endif

class vec2{
   public:
   /**
    * os vetores podem ser acessados com qualquer um dos padr�s listados abaixo:
    *     x,y
    */
   union {
      float array[2];
      struct{ float x,y; };
   };
   /**
    * construtores
    */
   inline vec2(){
      x = y = 0.0f;
   }
   inline vec2( const float v ){
      x = y = v;
   }
   inline vec2( const float v0, const float v1 ){
      x = v0;
      y = v1;
   }
   inline vec2( const vec2 &v ){
      *this = v;
   }
   inline vec2( const vec2 &a, const vec2 &b ){
      x = b.x - a.x;
      y = b.y - a.y;
   }
   bool operator==(const vec2&v) const {
      return memcmp(array, v.array, sizeof(float)*2)==0;
   }
   inline vec2& operator+=(const vec2& v){
     x+=v.x;
     y+=v.y;
     return (*this);
   }
   inline vec2& operator-=(const vec2& v){
     x-=v.x;
     y-=v.y;
     return (*this);
   }
   inline vec2 operator-(){
     return vec2(-x,-y);
   }
   inline vec2& operator*=(const vec2& v){
     x*=v.x;
     y*=v.y;
     return (*this);
   }
   inline vec2& operator/=(const vec2& v){
     x/=v.x;
     y/=v.y;
     return (*this);
   }
   //float version
   inline vec2& operator+=(const float v){
     x+=v;
     y+=v;
     return (*this);
   }
   inline vec2& operator-=(const float v){
     x-=v;
     y-=v;
     return (*this);
   }
   inline vec2& operator*=(const float v){
     x*=v;
     y*=v;
     return (*this);
   }
   inline vec2& operator/=(const float v){
     x/=v;
     y/=v;
     return (*this);
   }
   inline float& operator[](const int v){
     return array[v];
   }
};

#endif
