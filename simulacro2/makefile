CC = g++
all : tablero animal
rel : clean pull all
reload : rel

tablero : tablero.c ../shared/framework.h ../shared/definiciones.h 
	cc -o tablero tablero.c

animal: animal.c ../shared/framework.h ../shared/definiciones.h
	cc -o animal animal.c -lpthread

clean : 
	rm -rf *o *dat tablero animal
	for id in $(ipcs -m | awk 'NR>3 {print $2}'); do sudo ipcrm -m $id; done

pull : 
	git pull