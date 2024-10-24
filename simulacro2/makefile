CC = g++
all : tablero perro
reload : clean pull all

tablero : tablero.c ../shared/framework.h ../shared/definiciones.h 
	cc -o tablero tablero.c

perro: perro.c ../shared/framework.h ../shared/definiciones.h
	cc -o perro perro.c

clean : 
	rm -rf *o *dat tablero perro

pull : 
	git pull