#include "meufiltro.h"

void inicializarWidgetsMeuFiltro() {
	//widgets das opcoes de filtro
	adjustmentTamanhoLadrilho = gtk_adjustment_new(5.0, 3.0, 35.0, 2.0, 5.0, 0.0);
	adjustmentEspacamento = gtk_adjustment_new(0.0, 0.0, 10.0, 1.0, 5.0, 0.0);
	adjustmentAngulo = gtk_adjustment_new(0.0, 0.0, 90.0, 1.0, 5.0, 0.0);

	corDeFundo.red = 0;
	corDeFundo.green = 0;
	corDeFundo.blue = 0;
	corDeFundo.alpha = 1;

	widgetTamanhoLadrilho = gtk_spin_button_new (adjustmentTamanhoLadrilho, 1.0, 0);
	widgetEspacamento = gtk_spin_button_new (adjustmentEspacamento, 1.0, 0);
	widgetAngulo = gtk_spin_button_new (adjustmentAngulo, 1.0, 0);

	widgetCor = gtk_color_button_new_with_rgba(&corDeFundo);
	widgetRotacao = gtk_combo_box_text_new();
	widgetLadrilhoAleatorio = gtk_combo_box_text_new();
	
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgetRotacao), "1", "Fixo");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgetRotacao), "2", "Aleatório");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgetRotacao), "3", "Gradiente");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widgetRotacao), 0);

	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgetLadrilhoAleatorio), "1", "Rectilinear");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(widgetLadrilhoAleatorio), "2", "Aleatório");
	gtk_combo_box_set_active(GTK_COMBO_BOX(widgetLadrilhoAleatorio), 0);

	labelTamanhoLadrilho = gtk_label_new("Tamanho do ladrilho:");
	labelEspacamento = gtk_label_new("Espaçamento:");	
	labelTipoDeGeracao = gtk_label_new("Tipo de geração:");
	labelCorDeFundo = gtk_label_new("Cor de fundo:");
	labelTipoDeRotacao = gtk_label_new("Tipo de Rotação:");
	labelAnguloDeRotacao = gtk_label_new("Ângulo:");

	g_signal_connect(G_OBJECT(widgetTamanhoLadrilho), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetEspacamento), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetAngulo), "value-changed", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetCor), "color-set", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetLadrilhoAleatorio), "changed", G_CALLBACK(funcaoAplicar), NULL);
	g_signal_connect(G_OBJECT(widgetRotacao), "changed", G_CALLBACK(funcaoAplicar), NULL);
}

void adicionarWidgetsMeuFiltro(GtkWidget *container) {
	GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 20);
	gtk_container_add(GTK_CONTAINER(container), vbox);
	gtk_container_add(GTK_CONTAINER(vbox), labelTamanhoLadrilho);
	gtk_container_add(GTK_CONTAINER(vbox), widgetTamanhoLadrilho);
	gtk_container_add(GTK_CONTAINER(vbox), labelEspacamento);
	gtk_container_add(GTK_CONTAINER(vbox), widgetEspacamento);
	gtk_container_add(GTK_CONTAINER(vbox), labelTipoDeGeracao);
	gtk_container_add(GTK_CONTAINER(vbox), widgetLadrilhoAleatorio);
	gtk_container_add(GTK_CONTAINER(vbox), labelCorDeFundo);
	gtk_container_add(GTK_CONTAINER(vbox), widgetCor);
	gtk_container_add(GTK_CONTAINER(vbox), labelTipoDeRotacao);
	gtk_container_add(GTK_CONTAINER(vbox), widgetRotacao);
	gtk_container_add(GTK_CONTAINER(vbox), labelAnguloDeRotacao);
	gtk_container_add(GTK_CONTAINER(vbox), widgetAngulo);
}

Imagem meuFiltro(Imagem origem) {
	int tamanhoLadrilho = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetTamanhoLadrilho));
	int espacamento = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetEspacamento));
	int gerarAleatoriamente = !strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgetLadrilhoAleatorio)), "Aleatório");
	int tipoRotacao;
	int anguloUsuario = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widgetAngulo));
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widgetCor), &corDeFundo);

	GdkRGBA pixel;
	pixel.alpha = 1;

	int centroLadrilho = (int) tamanhoLadrilho / 2;
	int ladrilhosPorLinha = (int) origem.w / tamanhoLadrilho;
	int ladrilhosPorColuna = (int) origem.h / tamanhoLadrilho;
	int offset = ceil(sqrt(2 * pow(tamanhoLadrilho, 2))) / 2;
	Imagem destino;

	if (!strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgetRotacao)), "Fixo"))
		tipoRotacao = 1;
	else if(!strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgetRotacao)), "Aleatório"))
		tipoRotacao = 2;
	else
		tipoRotacao = 3;

	if(gerarAleatoriamente) {
		destino = alocarImagemPreenchida(origem.w + 2 * offset, origem.h + 2 * offset, origem.numCanais, corDeFundo);
		int quantidadeDeLadrilhos = ladrilhosPorLinha * ladrilhosPorColuna;
		
		for (int i = 0; i < quantidadeDeLadrilhos; i++) {
			int x = rand() % origem.w;
			int y = rand() % origem.h;

			pixel.red = origem.m[y][x][0] / 255.0f;
			pixel.green = origem.m[y][x][1] / 255.0f;
			pixel.blue = origem.m[y][x][2] / 255.0f;

			int angulo;
			switch (tipoRotacao) {
				case 1:
					angulo = anguloUsuario;
					break;

				case 2:
					angulo = rand() % 90;
					break;

				case 3:
					angulo = anguloGradiente(origem, novaCoordenada(x, y));
					break;
			}

			destino = desenharLadrilho(destino, novaCoordenada(x + offset, y + offset), tamanhoLadrilho, angulo, pixel);
		}
	} else {		
		if (espacamento == 0) {
			destino = alocarImagemPreenchida(ladrilhosPorLinha * tamanhoLadrilho + 2 * offset, ladrilhosPorColuna * tamanhoLadrilho + 2 * offset, origem.numCanais, corDeFundo);

			for (int y = centroLadrilho + offset; y < destino.h - offset; y += tamanhoLadrilho) {
				for (int x = centroLadrilho + offset; x < destino.w - offset; x += tamanhoLadrilho) {
					pixel.red = origem.m[y - offset][x - offset][0] / 255.0f;
					pixel.green = origem.m[y - offset][x - offset][1] / 255.0f;
					pixel.blue = origem.m[y - offset][x - offset][2] / 255.0f;

					int angulo;
					switch (tipoRotacao) {
						case 1:
							angulo = anguloUsuario;
							break;

						case 2:
							angulo = rand() % 90;
							break;

						case 3:
							angulo = anguloGradiente(origem, novaCoordenada(x - offset, y - offset));
							break;
					}

					destino = desenharLadrilho(destino, novaCoordenada(x, y), tamanhoLadrilho, angulo, pixel);
				}
				
			}
		} else {
			Imagem base = alocarImagemDimensao(ladrilhosPorLinha, ladrilhosPorColuna, origem.numCanais);
			destino = alocarImagemPreenchida(ladrilhosPorLinha * (tamanhoLadrilho + espacamento) - espacamento + 2 * offset, ladrilhosPorColuna * (tamanhoLadrilho + espacamento) - espacamento + 2 * offset, base.numCanais, corDeFundo);

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

					pixel.red = base.m[y][x][0] / 255.0f;
					pixel.green = base.m[y][x][1] / 255.0f;
					pixel.blue = base.m[y][x][2] / 255.0f;

					int angulo;
					switch (tipoRotacao) {
						case 1:
							angulo = anguloUsuario;
							break;

						case 2:
							angulo = rand() % 90;
							break;

						case 3:
							angulo = anguloGradiente(origem, novaCoordenada(p, q));
							break;
					}

					destino = desenharLadrilho(destino, novaCoordenada(i, j), tamanhoLadrilho, angulo, pixel);
				}
			}
		}
	}

	return destino;
}

Imagem desenharLadrilho (Imagem imagem, Coordenada centro, int tamanhoLadrilho, int angulo, GdkRGBA cor) {
	int centroLadrilho = (int) (tamanhoLadrilho / 2);
	Coordenada p1 = rotacionarPonto(novaCoordenada(centro.x - centroLadrilho, centro.y + centroLadrilho), centro, angulo);
 	Coordenada p2 = rotacionarPonto(novaCoordenada(centro.x + centroLadrilho, centro.y + centroLadrilho), centro, angulo);
 	Coordenada p3 = rotacionarPonto(novaCoordenada(centro.x - centroLadrilho, centro.y - centroLadrilho), centro, angulo);
 	Coordenada p4 = rotacionarPonto(novaCoordenada(centro.x + centroLadrilho, centro.y - centroLadrilho), centro, angulo);

	for (int y = p2.y; y <= p3.y; y++) {
		for (int x = p1.x; x <= p4.x; x++) {
			if (contidoNoLadrilho(novaCoordenada(x, y), p1, p2, p3, p4)) {
				imagem.m[y][x][0] = floor(cor.red * 255);
				imagem.m[y][x][1] = floor(cor.green * 255);
				imagem.m[y][x][2] = floor(cor.blue * 255);
			}
		}
	}

	return imagem;
}