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
#pragma once
//----------------------------------------------------------------------------------------------------
namespace GCX_CONFIG{
//----------------------------------------------------------------------------------------------------
#define MAX_PONTOS_FACE   100           /* N. maximo de pontos por face */
#define MAX_FACES_OBJETO  100           /* N. maximo de faces por objeto */
#define FOCO_OBS          500           /* Ponto do observador, no eixo z */
#define MAX_PONTOS        100           /* N. maximo de pontos */
#define MAX_FACES         100           /* N. maximo de faces */
#define MAX_CORES         8             /* N. maximo de cores */
#define MAXCOR            15            /* N. maximo de cores */
#define MAXMEMORIA        8191          /* ultima posicao enderecavel */
//----------------------------------------------------------------------------------------------------
#define NINST  39
#define ADD   1
#define ADDF  2
#define ADI   3
#define ADIF  4
#define BNG   5
#define BNGF  6
#define BNN   7
#define BNNF  8
#define BNP   9
#define BNPF  10
#define BNZ   11
#define BNZF  12
#define BPS   13
#define BPSF  14
#define BZR   15
#define BZRF  16
#define CNV   17
#define DVD   18
#define ESC   19
#define HLT   20
#define JMP   21
#define LDI   22
#define LDIF  23
#define LGT   24
#define LOD   25
#define LODF  26
#define MOV   27
#define MOVF  28
#define MUL   29
#define MULF  30
#define NEG   31
#define NEGF  32
#define RTR   33
#define STI   34
#define STIF  35
#define STO   36
#define STOF  37
#define SUB   38
#define SUBF  39
#define TME   40
//----------------------------------------------------------------------------------------------------
#define NREGS 6
#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6
#define N_RGB 6
//----------------------------------------------------------------------------------------------------
float _SleepFactor = 6.0f;
//----------------------------------------------------------------------------------------------------
}
