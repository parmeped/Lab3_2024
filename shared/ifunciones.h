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
#include <signal.h>



typedef struct tipo_mensajes mensaje;
struct tipo_mensajes 
{
    long long_dest;
    int int_rte;
    int int_evento;
    char char_mensaje[LARGO_TMENSAJE];
};

key_t creo_clave(int);

int creo_semaforo(int);
void inicio_semaforo(int, int, int);
void libero_semaforo(int, int);
/// @brief Libera semaforo y muestra un spinner que dura SegundosSpinner
/// @param  Id El id del array de semaforos
/// @param  Cual Que semaforo del array liberar
/// @param  SegundosSpinner los segundos que durará el spinner
void libero_semaforo_spinner(int, int, int);
/// @brief Libera semaforo y muestra un spinner que dura MiliSegundosSpinner
/// @param  Id El id del array de semaforos
/// @param  Cual Que semaforo del array liberar
/// @param  USegundosSpinner los milisegundos que durará el spinner
void libero_semaforo_mspinner(int, int, int);
void espera_semaforo(int, int);
int creo_id_cola_mensajes(int);
int borrar_mensajes(int);
int recibir_mensajes(int, long, mensaje*);
int enviar_mensaje(int, long, int, int, char*);
int randomNumber(int min, int max);
int randomNumberPrevSeed(int min, int max, int prevRandSeed);
void substring(const char *string, int position, int length, char *result);

#endif

