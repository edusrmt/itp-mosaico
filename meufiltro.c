#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	adjustmentTamanhoLadrilho = gtk_adjustment_new(5.0, 3.0, 35.0, 2.0, 5.0, 0.0);
	adjustmentEspacamento = gtk_adjustment_new(0.0, 0.0, 10.0, 1.0, 5.0, 0.0);
	adjustmentAngulo = gtk_adjustment_new(0.0, 0.0, 90.0, 1.0, 5.0, 0.0);

	widgetTamanhoLadrilho = gtk_spin_button_new (adjustmentTamanhoLadrilho, 1.0, 0);
	widgetEspacamento = gtk_spin_button_new (adjustmentEspacamento, 1.0, 0);
	widgetLadrilhoAleatorio = gtk_check_button_new_with_label("Distribuir Aleatoriamente");
	widgetCor = gtk_color_button_new ();
	widgetRotacao = gtk_combo_box_new ();
	widgetAngulo = gtk_spin_button_new (adjustmentAngulo, 1.0, 0);

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
	gtk_container_add(GTK_CONTAINER(vbox), widgetCor);
	gtk_container_add(GTK_CONTAINER(vbox), widgetRotacao);
	gtk_container_add(GTK_CONTAINER(vbox), widgetAngulo);
}

Imagem meuFiltro(Imagem origem) {
	int tamanhoLadrilho = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetTamanhoLadrilho));
	int espacamento = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetEspacamento));
	int centroLadrilho = (int) tamanhoLadrilho / 2;
	int ladrilhosPorLinha = (int) origem.w / tamanhoLadrilho;
	int ladrilhosPorColuna = (int) origem.h / tamanhoLadrilho;
	int offset = ceil(sqrt(2 * pow(tamanhoLadrilho, 2))) / 2;
	Imagem destino;

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widgetLadrilhoAleatorio))) {
		destino = alocarImagemPreenchida(origem.w + 2 * offset, origem.h + 2 * offset, origem.numCanais);
		int quantidadeDeLadrilhos = ladrilhosPorLinha * ladrilhosPorColuna;
		
		for (int i = 0; i < quantidadeDeLadrilhos; i++) {
			int x = rand() % origem.w;
			int y = rand() % origem.h;

			int angulo = anguloGradiente(origem, novaCoordenada(x, y));
			printf("%d | %d\n", x, y);
			destino = desenharLadrilho(destino, novaCoordenada(x + offset, y + offset), tamanhoLadrilho, angulo, origem.m[y][x][0], origem.m[y][x][1], origem.m[y][x][2]);
		}
	} else {		
		if (espacamento == 0) {
			destino = alocarImagemPreenchida(ladrilhosPorLinha * tamanhoLadrilho + 2 * offset, ladrilhosPorColuna * tamanhoLadrilho + 2 * offset, origem.numCanais);

			for (int y = centroLadrilho + offset; y < destino.h - offset; y += tamanhoLadrilho) {
				for (int x = centroLadrilho + offset; x < destino.w - offset; x += tamanhoLadrilho) {
					destino.m[y][x][0] = origem.m[y - offset][x - offset][0];
					destino.m[y][x][1] = origem.m[y - offset][x - offset][1];
					destino.m[y][x][2] = origem.m[y - offset][x - offset][2];

					int angulo = anguloGradiente(origem, novaCoordenada(x - offset, y - offset));
					destino = desenharLadrilho(destino, novaCoordenada(x, y), tamanhoLadrilho, angulo, origem.m[y - offset][x - offset][0], origem.m[y - offset][x - offset][1], origem.m[y - offset][x - offset][2]);
				}
				
			}
		} else {
			Imagem base = alocarImagemDimensao(ladrilhosPorLinha, ladrilhosPorColuna, origem.numCanais);
			destino = alocarImagemPreenchida(ladrilhosPorLinha * (tamanhoLadrilho + espacamento) - espacamento + 2 * offset, ladrilhosPorColuna * (tamanhoLadrilho + espacamento) - espacamento + 2 * offset, base.numCanais);

			for (int j = 0; j < base.h; j++) {
				for (int i = 0; i < base.w; i++) {
					int x = i * tamanhoLadrilho + centroLadrilho;
					int y = j * tamanhoLadrilho + centroLadrilho;

					base.m[j][i][0] = origem.m[y][x][0];
					base.m[j][i][1] = origem.m[y][x][1];
					base.m[j][i][2] = origem.m[y][x][2];
				}
			}

			for (int y = 0; y < base.h; y++) {
				for(int x = 0; x < base.w; x++) {
					int i = offset + x * (espacamento + tamanhoLadrilho) + tamanhoLadrilho / 2;
					int j = offset + y * (espacamento + tamanhoLadrilho) + tamanhoLadrilho / 2;
					int p = x * tamanhoLadrilho + centroLadrilho;
					int q = y * tamanhoLadrilho + centroLadrilho;

					destino.m[j][i][0] = base.m[y][x][0];
					destino.m[j][i][1] = base.m[y][x][1];
					destino.m[j][i][2] = base.m[y][x][2];					

					int angulo = anguloGradiente(origem, novaCoordenada(p, q));
					destino = desenharLadrilho(destino, novaCoordenada(i, j), tamanhoLadrilho, angulo, base.m[y][x][0], base.m[y][x][1], base.m[y][x][2]);
				}
			}
		}
	}

	return destino;
}

Imagem desenharLadrilho (Imagem imagem, Coordenada centro, int tamanhoLadrilho, int angulo, int r, int g, int b) {
	int centroLadrilho = (int) (tamanhoLadrilho / 2);
	//angulo = converterAngulo(angulo);
	Coordenada p1 = rotacionarPonto(novaCoordenada(centro.x - centroLadrilho, centro.y + centroLadrilho), centro, angulo);
 	Coordenada p2 = rotacionarPonto(novaCoordenada(centro.x + centroLadrilho, centro.y + centroLadrilho), centro, angulo);
 	Coordenada p3 = rotacionarPonto(novaCoordenada(centro.x - centroLadrilho, centro.y - centroLadrilho), centro, angulo);
 	Coordenada p4 = rotacionarPonto(novaCoordenada(centro.x + centroLadrilho, centro.y - centroLadrilho), centro, angulo);

	for (int y = p2.y; y <= p3.y; y++) {
		for (int x = p1.x; x <= p4.x; x++) {
			if (contidoNoLadrilho(novaCoordenada(x, y), p1, p2, p3, p4)) {
				imagem.m[y][x][0] = r;
				imagem.m[y][x][1] = g;
				imagem.m[y][x][2] = b;
			}
		}
	}

	return imagem;
}