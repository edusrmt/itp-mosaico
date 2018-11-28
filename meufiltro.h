#ifndef MEUFILTRO_H
#define MEUFILTRO_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "imagem.h"
#include "geometria.h"

//declare aqui os seus widgets
GtkWidget *widgetTamanhoLadrilho;
GtkWidget *widgetLadrilhoAleatorio;
GtkWidget *widgetEspacamento;
GtkWidget *widgetCor;
GtkWidget *widgetRotacao;
GtkWidget *widgetAngulo;

GtkAdjustment *adjustmentTamanhoLadrilho;
GtkAdjustment *adjustmentEspacamento;
GtkAdjustment *adjustmentAngulo;

void inicializarWidgetsMeuFiltro();
void adicionarWidgetsMeuFiltro(GtkWidget *container);

Imagem meuFiltro(Imagem origem);
Imagem criarImagemComBase (Imagem base, int tamanhoLadrilho, int espacamento);
Imagem desenharLadrilho (Imagem imagemAtual, Coordenada centro, int tamanhoLadrilho, int angulo, int r, int g, int b);

//esta funcao esta implementada em filtroGtk.c, nao precisa alterar
void funcaoAplicar(GtkWidget *widget, gpointer data);

#endif


