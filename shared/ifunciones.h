#ifndef _IFUNCIONES_H
#define _IFUNCIONES_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>

#define CLAVE_BASE 33
#define SEMAFORO0 0


#define LARGO_TMENSAJE 1024

typedef struct tipo_mensajes mensaje;
struct tipo_mensajes 
{
    long long_dest;
    int int_rte;
    int int_evento;
    char char_mensaje[LARGO_TMENSAJE];
};

key_t creo_clave(int);
void* creo_memoria(int, int*, int);
int creo_semaforo(int);
void inicio_semaforo(int, int, int);
void levanta_semaforo(int, int);
void espera_semaforo(int, int);
int creo_id_cola_mensajes(int);
int borrar_mensajes(int);
int recibir_mensajes(int, long, mensaje*);
int enviar_mensaje(int, long, int, int, char*);


#endif

