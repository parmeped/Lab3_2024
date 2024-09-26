CC = g++
all : readMem writeMem
reload : clean pull all

readMem : readMem.c ../shared/framework.h ../shared/definiciones.h 
	cc -o readMem readMem.c

writeMem : writeMem.c ../shared/framework.h ../shared/definiciones.h 
	cc -o writeMem writeMem.c

clean : 
	rm -rf *o *dat readMem writeMem

pull : 
	git pull