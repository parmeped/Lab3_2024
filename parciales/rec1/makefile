CC = g++
all : panel equipo
r : clean memClean pull all
rel : r
reload : r

panel : panel.c ../../shared/framework.h ../../shared/definiciones.h 
	cc -o panel panel.c

equipo : equipo.c ../../shared/framework.h ../../shared/definiciones.h
	cc -o equipo equipo.c

clean : 
	rm -rf *o *dat panel equipo	

memClean :
	for id in $(ipcs -m | awk 'NR>3 {print $2}'); do ipcrm -m $id; done

pull :
	git pull

