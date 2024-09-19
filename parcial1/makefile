CC = g++
all : derivador
reload : clean pull all

derivador : derivador.c ../shared/framework.h ../shared/definiciones.h 
	cc -o derivador derivador.c

clean : 
	rm -rf *o *dat derivador

pull : 
	git pull