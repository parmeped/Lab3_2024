CC = g++
all : tableroE jugadores
r : clean memClean pull all
reload : r

tableroE : tableroE.c ../shared/framework.h ../shared/definiciones.h 
	cc -o tableroE tableroE.c

jugadores: jugadores.c ../shared/framework.h ../shared/definiciones.h
	cc -o jugadores jugadores.c -lpthread

clean : 
	rm -rf *o *dat tableroE jugadores	

memClean:
	for id in $(ipcs -m | awk 'NR>3 {print $2}'); do ipcrm -m $id; done

pull : 
	git pull