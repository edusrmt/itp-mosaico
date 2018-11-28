all:
	gcc imagem.c -c `pkg-config gtk+-3.0 --cflags --libs` 
	gcc geometria.c -c `pkg-config gtk+-3.0 --cflags --libs` -lm
	gcc meufiltro.c -c `pkg-config gtk+-3.0 --cflags --libs`
	gcc filtroGtk.c `pkg-config gtk+-3.0 --cflags --libs` meufiltro.o geometria.o imagem.o -lm
