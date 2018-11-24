#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	adjustmentTamanhoLadrilho = gtk_adjustment_new(5.0, 1.0, 35.0, 2.0, 5.0, 0.0);
	adjustmentEspacamento = gtk_adjustment_new(0.0, 0.0, 10.0, 1.0, 5.0, 0.0);

	widgetTamanhoLadrilho = gtk_spin_button_new (adjustmentTamanhoLadrilho, 1.0, 0);
	widgetEspacamento = gtk_spin_button_new (adjustmentEspacamento, 1.0, 0);
	widgetLadrilhoAleatorio = gtk_check_button_new_with_label("Distribuir Aleatoriamente");

	g_signal_connect(G_OBJECT(widgetTamanhoLadrilho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);	
	g_signal_connect(G_OBJECT(widgetEspacamento), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox), widgetTamanhoLadrilho);
	gtk_container_add(GTK_CONTAINER(vbox), widgetEspacamento);
	gtk_container_add(GTK_CONTAINER(vbox), widgetLadrilhoAleatorio);
}

Imagem meuFiltro(Imagem origem) {
	int tamanhoLadrilho = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetTamanhoLadrilho));
	int espacamento = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetEspacamento));
	int centroLadrilho = (int) tamanhoLadrilho / 2;
	int ladrilhosPorLinha = (int) origem.w / tamanhoLadrilho;
	int ladrilhosPorColuna = (int) origem.h / tamanhoLadrilho;

	Imagem destino;	

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetLadrilhoAleatorio))) {
		// Poisson Disc Sampling
	} else {
		if (espacamento == 0) {
			destino = alocarImagemDimensao(ladrilhosPorLinha * tamanhoLadrilho, ladrilhosPorColuna * tamanhoLadrilho, origem.numCanais);
			
			for (int y = centroLadrilho; y < destino.h - 1; y += tamanhoLadrilho) {
				for (int x = centroLadrilho; x < destino.w - 1; x += tamanhoLadrilho) {
					for (int j = y - centroLadrilho; j <= y + centroLadrilho; j++) {
						for (int i = x - centroLadrilho; i <= x + centroLadrilho; i++) {
							destino.m[j][i][0] = origem.m[y][x][0];
							destino.m[j][i][1] = origem.m[y][x][1];
							destino.m[j][i][2] = origem.m[y][x][2];
						}
					}
				}
			}
		} else {
			destino = alocarImagemDimensao(ladrilhosPorLinha * (tamanhoLadrilho + espacamento) + espacamento, ladrilhosPorColuna * (tamanhoLadrilho + espacamento) + espacamento, origem.numCanais);
			Imagem base = alocarImagemDimensao(ladrilhosPorLinha, ladrilhosPorColuna, origem.numCanais);
			int i = 0, j = 0;

			for (int j = 0; j < base.h; j++) {
				for (int i = 0; i < base.w; i++) {
					int x = i * tamanhoLadrilho + centroLadrilho;
					int y = j * tamanhoLadrilho + centroLadrilho;

					base.m[j][i][0] = origem.m[y][x][0];
					base.m[j][i][1] = origem.m[y][x][1];
					base.m[j][i][2] = origem.m[y][x][2];
				}
			}

			destino = criarImagemComBase(base, tamanhoLadrilho, espacamento);
		}
	}

	return destino;
}

Imagem criarImagemComBase (Imagem base, int tamanhoLadrilho, int espacamento) {
	Imagem retorno = alocarImagemDimensao(base.w * (tamanhoLadrilho + espacamento) + espacamento, base.h * (tamanhoLadrilho + espacamento) + espacamento, base.numCanais);

	for (int y = 0; y < retorno.h; y++){
		for(int x = 0; x < retorno.w; x++){
			retorno.m[y][x][0] = 0;
			retorno.m[y][x][1] = 255;
			retorno.m[y][x][2] = 0;
		}
	}

	for (int y = 0; y < base.h; y++){
		for(int x = 0; x < base.w; x++){

			for (int j = 0; j < tamanhoLadrilho; j++) {
				for (int i = 0; i < tamanhoLadrilho; i++) {
					int p = espacamento + x * (espacamento + tamanhoLadrilho);
					int q = espacamento + y * (espacamento + tamanhoLadrilho);

					retorno.m[q + j][p + i][0] = base.m[y][x][0];
					retorno.m[q + j][p + i][1] = base.m[y][x][1];
					retorno.m[q + j][p + i][2] = base.m[y][x][2];
				}
			}
		}
	}	

	return retorno;
}