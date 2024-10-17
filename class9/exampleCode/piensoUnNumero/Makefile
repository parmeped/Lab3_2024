CC 		= g++ 

all : jugador pienso

jugador : jugador.c funciones.h definiciones.h funciones.o
	cc -o jugador jugador.c funciones.o -pthread

pienso : pienso.c funciones.h definiciones.h funciones.o
	cc -o pienso pienso.c funciones.o 

funciones.o : funciones.c funciones.h
	cc -c funciones.c
	
clean: 
	rm -rf *o pienso jugador *~
