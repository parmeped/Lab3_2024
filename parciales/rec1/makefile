CC = g++
all : file1 file2
r : clean memClean pull all
rel : r
reload : r

file1 : file1.c ../../shared/framework.h ../../shared/definiciones.h 
	cc -o file1 file1.c

file2 : file2.c ../../shared/framework.h ../../shared/definiciones.h
	cc -o file2 file2.c

clean : 
	rm -rf *o *dat file1 file2	

memClean :
	for id in $(ipcs -m | awk 'NR>3 {print $2}'); do ipcrm -m $id; done

pull :
	git pull

run : all 
	gnome-terminal ./file1
	gnome-terminal ./file2 1
	gnome-terminal ./file2 2