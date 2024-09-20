CC = g++
all : derivador caja1 caja2
reload : clean pull all

derivador : derivador.c ../shared/framework.h ../shared/definiciones.h 
	cc -o derivador derivador.c

caja1: caja1.c ../shared/framework.h ../shared/definiciones.h
	cc -o caja1 caja1.c

caja2: caja2.c ../shared/framework.h ../shared/definiciones.h
	cc -o caja2 caja2.c

clean :
	rm -rf *o *dat derivador caja1 caja2

pull : 
	git pull