CC = g++
all : tablero animal
reload : clean pull all

tablero : tablero.c ../shared/framework.h ../shared/definiciones.h 
	cc -o tablero tablero.c

animal: animal.c ../shared/framework.h ../shared/definiciones.h
	cc -o animal animal.c -pthread

clean : 
	rm -rf *o *dat tablero animal

pull : 
	git pull