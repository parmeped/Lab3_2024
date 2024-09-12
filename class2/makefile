# Esto es un comentario.
CC = g++
all : repositor supermercado

supermercado : supermercado.c ../shared/funciones.h ../shared/definiciones.h 
	cc -o supermercado supermercado.c

repositor : repositor.c ../shared/funciones.h ../shared/definiciones.h 
	cc -o repositor repositor.c

clean : 
	rm -rf *o supermercado repositor