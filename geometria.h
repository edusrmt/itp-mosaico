#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "imagem.h"

typedef struct Coordenada
{
	int x;
	int y;
} Coordenada;

Coordenada novaCoordenada(int x, int y);
Coordenada rotacionarPonto(Coordenada ponto, Coordenada centro, int angulo);
int contidoNoLadrilho (Coordenada ponto, Coordenada p1, Coordenada p2, Coordenada p3, Coordenada p4);
int anguloGradiente (Imagem imagem, Coordenada centro);

// Funções auxuliares
float areaTriangulo(Coordenada a, Coordenada b, Coordenada c);
int converterAngulo (int angulo);
int escalaCinzenta (int r, int g, int b);

#endif