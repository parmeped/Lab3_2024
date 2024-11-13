CC = g++
all : panel cci
r : clean memClean pull all
reload : r

panel : panel.c ../shared/framework.h ../shared/definiciones.h 
	cc -o panel panel.c

cci: cci.c ../shared/framework.h ../shared/definiciones.h
	cc -o cci cci.c -lpthread

clean : 
	rm -rf *o *dat panel cci	

memClean:
	for id in $(ipcs -m | awk 'NR>3 {print $2}'); do ipcrm -m $id; done

pull : 
	git pull