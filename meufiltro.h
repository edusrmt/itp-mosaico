#ifndef MEUFILTRO_H
#define MEUFILTRO_H

#include <gtk/gtk.h>
#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include "imagem.h"

//declare aqui os seus widgets
GtkWidget *widgetTamanhoLadrilho;
GtkWidget *widgetLadrilhoAleatorio;
GtkWidget *widgetEspacamento;

GtkAdjustment *adjustmentTamanhoLadrilho;
GtkAdjustment *adjustmentEspacamento;

Imagem meuFiltro(Imagem origem);
Imagem criarImagemComBase (Imagem base, int tamanhoLadrilho, int espacamento);
void inicializarWidgetsMeuFiltro();
void adicionarWidgetsMeuFiltro(GtkWidget *container);

//esta funcao esta implementada em filtroGtk.c, nao precisa alterar
void funcaoAplicar(GtkWidget *widget, gpointer data);

#endif


