CC = g++
all : read write
reload : clean pull all

read : read.c ../shared/framework.h ../shared/definiciones.h 
	cc -o read read.c

write : write.c ../shared/framework.h ../shared/definiciones.h 
	cc -o write write.c

clean : 
	rm -rf *o *dat read write

pull : 
	git pull