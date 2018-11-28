#include "geometria.h"

Coordenada novaCoordenada (int x, int y) {
	Coordenada coordenada = {x, y};

	return coordenada;
}

Coordenada rotacionarPonto (Coordenada ponto, Coordenada centro, int angulo) {
	float anguloRadiano = M_PI / 180 * angulo;
	Coordenada pontoRotacionado;
	ponto.x -= centro.x;
	ponto.y -= centro.y;

	pontoRotacionado.x = (int) (cos(anguloRadiano) * ponto.x - sin(anguloRadiano) * ponto.y);
	pontoRotacionado.y = (int) (cos(anguloRadiano) * ponto.y + sin(anguloRadiano) * ponto.x);
	pontoRotacionado.x += centro.x;
	pontoRotacionado.y = centro.y - pontoRotacionado.y;

	return pontoRotacionado;
}

int contidoNoLadrilho (Coordenada ponto, Coordenada p1, Coordenada p2, Coordenada p3, Coordenada p4) {
	float areaQuadrado = areaTriangulo(p1, p2, p3) + areaTriangulo(p2, p3, p4);
	float a1 = areaTriangulo(ponto, p1, p2);
	float a2 = areaTriangulo(ponto, p2, p4);
	float a3 = areaTriangulo(ponto, p3, p4);
	float a4 = areaTriangulo(ponto, p1, p3);

	return areaQuadrado == a1 + a2 + a3 + a4;
}

int anguloGradiente (Imagem imagem, Coordenada centro) {
	int gX = 0, gY = 0;

	for (int j = -1; j <= 1; j++) {
    	for (int i = -1; i <= 1; i++) {
    		gX += i * escalaCinzenta(imagem.m[centro.y + j][centro.x + i][0], imagem.m[centro.y + j][centro.x + i][1], imagem.m[centro.y + j][centro.x + i][2]); 
    		gY += j * escalaCinzenta(imagem.m[centro.y + j][centro.x + i][0], imagem.m[centro.y + j][centro.x + i][1], imagem.m[centro.y + j][centro.x + i][2]);
    	}
	}

	return converterAngulo(ceil(atan2(gY, gX) * 180 / M_PI));
}

// Funções auxiliares

float areaTriangulo (Coordenada a, Coordenada b, Coordenada c) {
	return fabs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0);
}

int converterAngulo (int angulo) {
	if(angulo < 0)
		angulo += 360;

	while (angulo >= 90)
		angulo -= 90;

	return angulo;
}

int escalaCinzenta (int r, int g, int b) {
	return r * 0.3f + g * 0.59f + b * 0.11f;
}

