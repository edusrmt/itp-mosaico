#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	adjustment = gtk_adjustment_new(10.0, 0.0, 100.0, 1.0, 5.0, 0.0);
	widgetTamanhoLadrilho = gtk_spin_button_new (adjustment, 1.0, 0);
	g_signal_connect(G_OBJECT(widgetTamanhoLadrilho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox), widgetTamanhoLadrilho);
}

Imagem meuFiltro(Imagem origem) {
	int i, j;
	Imagem destino = alocarImagem(origem);
	int tamanhoLadrilho = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetTamanhoLadrilho));
	
	for (int x = 0; x < destino.w; x += tamanhoLadrilho) {
		for (int y = 0; y < destino.h; y += tamanhoLadrilho) {

			for (int i = 0; i < tamanhoLadrilho; i++) {
				for (int j = 0; j < tamanhoLadrilho; j++) {
					if (x + i >= destino.w)
						break;

					if (y + j >= destino.h)
						break;

					destino.m[y + j][x + i][0] = origem.m[y][x][0];
					destino.m[y + j][x + i][1] = origem.m[y][x][1];
					destino.m[y + j][x + i][2] = origem.m[y][x][2];
				}
			} 

		}
	}
	
	return destino;
}