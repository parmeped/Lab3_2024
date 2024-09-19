CC = g++
all : derivador caja
reload : clean pull all

derivador : derivador.c ../shared/framework.h ../shared/definiciones.h 
	cc -o derivador derivador.c

caja: caja.c ../shared/framework.h ../shared/definiciones.h
	cc -o caja caja.c

clean : 
	rm -rf *o *dat derivador caja

pull : 
	git pull