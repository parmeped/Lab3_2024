CC = g++
all : carga
reload : clean pull all

carga : carga.c ../../shared/framework.h ../../shared/definiciones.h 
	cc -o carga carga.c

clean : 
	rm -rf *o *dat carga

pull : 
	git pull