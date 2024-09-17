CC = g++
all : carga reservas
reload : clean pull all

carga : carga.c ../../shared/framework.h ../../shared/definiciones.h 
	cc -o carga carga.c

reservas : reservas.c ../../shared/framework.h ../../shared/definiciones.h 
	cc -o reservas reservas.c

clean : 
	rm -rf *o *dat carga reservas

pull : 
	git pull