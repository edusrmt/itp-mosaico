#ifndef IMAGEM_H
#define IMAGEM_H

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <math.h>
#include <glib.h>
#include <stdlib.h>

typedef struct Imagem {
	unsigned char ***m;
	int w;
	int h;
	int numCanais;
} Imagem;


Imagem original, resultado;
Imagem alocarImagem(Imagem referencia);
Imagem alocarImagemDimensao(int w, int h, int numCanais);
Imagem alocarImagemPreenchida (int w, int h, int numCanais, GdkRGBA cor);
void desalocarImagem(Imagem referencia);

#endif


