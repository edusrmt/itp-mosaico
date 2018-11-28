#include "imagem.h"

Imagem alocarImagem(Imagem referencia) {
	Imagem img;
	int i, j;
	img.h = referencia.h;
	img.w = referencia.w;
	img.numCanais = referencia.numCanais;
	img.m = malloc(sizeof(guchar **)*img.h);
	for(i = 0; i < img.h; i++) {
		img.m[i] = malloc(sizeof(guchar *)*img.w);
		for(j = 0; j < img.w; j++)
			img.m[i][j] = malloc(sizeof(guchar)*img.numCanais);
	}
	return img;
}

Imagem alocarImagemDimensao(int w, int h, int numCanais) {
	Imagem img;
	int i, j;
	img.h = h;
	img.w = w;
	img.numCanais = numCanais;
	img.m = malloc(sizeof(guchar **)*img.h);
	for(i = 0; i < img.h; i++) {
		img.m[i] = malloc(sizeof(guchar *)*img.w);
		for(j = 0; j < img.w; j++)
			img.m[i][j] = malloc(sizeof(guchar)*img.numCanais);
	}
	return img;
}

Imagem alocarImagemPreenchida (int w, int h, int numCanais) {
	Imagem img = alocarImagemDimensao(w, h, numCanais);

	for (int y = 0; y < img.h; y++) {
		for (int x = 0; x < img.w; x++) {
			img.m[y][x][0] = 0;
			img.m[y][x][1] = 255;
			img.m[y][x][2] = 0;
		}
	}

	return img;
}

void desalocarImagem(Imagem referencia) {
	for(int i = 0; i < referencia.h; i++) {
		for(int j = 0; j < referencia.w; j++) {
			free(referencia.m[i][j]);
		}
		free(referencia.m[i]);
	}
	free(referencia.m);
}

