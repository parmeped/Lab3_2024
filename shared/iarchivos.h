#ifndef _IARCHIVOS_H
#define _IARCHIVOS_H
#include <stdio.h>

FILE* abrir_archivo_lectura(char* path);
FILE* abrir_archivo_escritura(char* path);
FILE* append_archivo(char* path);
FILE* abrir_archivo(char* path, char* modo);
void cerrar_archivo(FILE*);

#endif