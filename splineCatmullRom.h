#ifndef splineCatmulRom__h__
#define splineCatmulRom__h__

#include "vecOP.h"

/*
q(t) = 0.5 * (1.0f,t,t2,t3)  *  	

[  0  2  0  0 ]  [P0]
[ -1  0  1  0 ]* [P1]
[  2 -5  4 -1 ]  [P2]
[ -1  3 -3  1 ]  [P3]

q(t) = 0.5 *((2 * P1) + 
             (-P0 + P2) * t + 
             (2*P0 - 5*P1 + 4*P2 - P3) * t2 + 
             (-P0 + 3*P1- 3*P2 + P3) * t3)

o valor de t deve estar entre 0 e 1
*/

static inline vec3 splineCatmullRom(vec3 P0,vec3 P1, vec3 P2, vec3 P3,float t){
return 0.5f *((2.0f * P1) + 
              (P2 - P0) * t + 
              (2.0f*P0 - 5.0f*P1 + 4.0f*P2 - P3) * (t*t) + 
              (3.0f*P1 - P0 - 3.0f*P2 + P3) * (t*t*t) );
}

static inline vec2 splineCatmullRom(vec2 P0,vec2 P1, vec2 P2, vec2 P3,float t){
return 0.5f *((2.0f * P1) + 
              (P2 - P0) * t + 
              (2.0f*P0 - 5.0f*P1 + 4.0f*P2 - P3) * (t*t) + 
              (3.0f*P1 - P0 - 3.0f*P2 + P3) * (t*t*t) );
}

#endif