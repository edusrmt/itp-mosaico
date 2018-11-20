#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	adjustment = gtk_adjustment_new(5.0, 0.0, 100.0, 1.0, 5.0, 0.0);
	widgetTamanhoLadrilho = gtk_spin_button_new (adjustment, 1.0, 0);
	widgetLadrilhoAleatorio = gtk_check_button_new_with_label("Distribuir Aleatoriamente");
	g_signal_connect(G_OBJECT(widgetTamanhoLadrilho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {

	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox), widgetTamanhoLadrilho);
	gtk_container_add(GTK_CONTAINER(vbox), widgetLadrilhoAleatorio);
}

Imagem meuFiltro(Imagem origem) {
	int i, j;
	//Imagem destino = alocarImagemDimensao(origem.w*2, origem.h*2, origem.numCanais);
	Imagem destino = alocarImagem(origem);
	int tamanhoLadrilho = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetTamanhoLadrilho));
	int centroLadrilho = (int) tamanhoLadrilho / 2;
	
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetLadrilhoAleatorio))) {

	}

	for (int x = 0; x < destino.w; x += tamanhoLadrilho) {
		for (int y = 0; y < destino.h; y += tamanhoLadrilho) {

			for (int i = 0; i < tamanhoLadrilho; i++) {
				for (int j = 0; j < tamanhoLadrilho; j++) {
					if (x + i >= destino.w)
						break;

					if (y + j >= destino.h)
						break;

					if (x + centroLadrilho >= destino.w)
						x = destino.w - 1;

					if (y + centroLadrilho >= destino.h)
						break;

					destino.m[y + j][x + i][0] = origem.m[y + centroLadrilho][x + centroLadrilho][0];
					destino.m[y + j][x + i][1] = origem.m[y + centroLadrilho][x + centroLadrilho][1];
					destino.m[y + j][x + i][2] = origem.m[y + centroLadrilho][x + centroLadrilho][2];
				}
			} 

		}
	}
	
	return destino;
}