CC = g++
all : cajero
reload : clean pull all

cajero : cajero.c ../../shared/framework.h ../../shared/definiciones.h 
	cc -o cajero cajero.c

clean : 
	rm -rf *o *dat cajero

pull : 
	git pull