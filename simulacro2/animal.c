#include <pthread.h>
#include "def.h"
#include "../shared/framework.h"

int id_cola_mensajes;
pthread_mutex_t mutex;
int memoryId, statusMemId;

#define SALIR			0

const char* destinoToString(Destinos destino) 
{
    switch (destino) {
        case MSG_PERRO:
            return "Perro";
        case MSG_GATO:
            return "Gato";
        case MSG_CONEJO:
            return "Conejo";
        default:
            return "Desconocido";
    }
}

const int destinoToInt(Destinos destino) 
{
    switch (destino) {
        case MSG_PERRO:
            return 0;
        case MSG_GATO:
            return 1;
        case MSG_CONEJO:
            return 2;
        default:
            return -1;
    }
}

const char* eventoToString(Eventos evento) 
{
    switch (evento) {
        case EVT_CORRO:
            return "Corro";
        case EVT_FIN:
            return "Fin";
        default:
            return "Desconocido";
    }
}

void generarEventoCorrer(Destinos remitente, int cantidad_pasos, int pasos) 
{
    mensaje msg;
    msg.long_dest = remitente;
    msg.int_rte = 0;
    msg.int_evento = EVT_CORRO;
    printf("Generando evento %s\n", eventoToString(msg.int_evento));
    printf("Cantidad de pasos %d\n", cantidad_pasos);
    printf("Pasos %d\n", pasos);
    enviar_mensaje(id_cola_mensajes, MSG_TABLERO, remitente, msg.int_evento, "");
    spinner(1);
}

void sumoPasos(int pasos, Destinos destino) 
{
    status *memoria = NULL;
    memoria = (status*)creo_memoria(sizeof(status) * RUNNERS_AMOUNT, &memoryId, CLAVE_BASE);
    memoria[destinoToInt(destino)].totalSteps += pasos;    
}

void *funcionAnimal(void *input)
{
	mensaje	msg;
    int cantidad_pasos = 0;
    int pasos = 0;
    sprintStatus *memoriaStatus = NULL;
    memoriaStatus = (sprintStatus*)creo_memoria(sizeof(sprintStatus), &statusMemId, CLAVE_BASE_2);
	
    while(memoriaStatus->run == 0)
	{
		logInfof("Esperando inicio carrera, Thread: %s", destinoToString(((struct animal_config*)input)->destino));
		spinner(1);
	}

    while(memoriaStatus->run == 1)
	{
        logInfof("Esperando mensaje para %s", destinoToString(((struct animal_config*)input)->destino));
        recibir_mensajes(id_cola_mensajes, ((struct animal_config*)input)->destino, &msg);
        if (msg.int_evento == EVT_FIN)
        {
            logInfof("Finalizado thread: %s\n", destinoToString(((struct animal_config*)input)->destino));
            break;
        }
    	printf("Thread: %s\n", destinoToString(((struct animal_config*)input)->destino));
        printf("MinSpeed: %d, MaxSpeed: %d\n", ((struct animal_config*)input)->min_speed, ((struct animal_config*)input)->max_speed);
		pthread_mutex_lock (&mutex);
            pasos += randomNumber(((struct animal_config*)input)->min_speed, ((struct animal_config*)input)->max_speed);
            cantidad_pasos++;
            generarEventoCorrer(((struct animal_config*)input)->destino, cantidad_pasos, pasos);
            sumoPasos(pasos, ((struct animal_config*)input)->destino);
            if (pasos >= max_pasos)
            {
                break;
            }
        pthread_mutex_unlock (&mutex);	
	};
	printf ("Hijo  : Termino\n");
	pthread_exit ((void *)"Listo");
}

int menu(void)
{
    int opcion;

    printf("Menu\n\n");
    printf("0.\tSalir\n\n");
    printf("1.\tEmpezar\n\n");
    printf("Elija opcion: \n");
    fflush(stdin);  
    while((scanf(" %d", &opcion) != 1)
          || (opcion < 0))    
    {
      fflush(stdin);                 
      printf("No valido\n\n");
      printf("Elija opcion: \n");
    }
    return opcion;
}                

int main()
{
	pthread_t 		idHilo;
	pthread_attr_t 	atributos;
    int opcion;
    
    status *memoria = NULL;
	memoria = (status*)creo_memoria(sizeof(status) * RUNNERS_AMOUNT, &memoryId, CLAVE_BASE);
    sprintStatus *memoryStatus = NULL;
    memoryStatus = (sprintStatus*)creo_memoria(sizeof(sprintStatus), &statusMemId, CLAVE_BASE_2);

	struct animal_config *gato_config = (struct animal_config *)malloc(sizeof(struct animal_config));
    struct animal_config *perro_config = (struct animal_config *)malloc(sizeof(struct animal_config));
    struct animal_config *conejo_config = (struct animal_config *)malloc(sizeof(struct animal_config));

    gato_config->min_speed = min_gato;
    gato_config->max_speed = max_gato;
    gato_config->destino = MSG_GATO;

    memoria[destinoToInt(MSG_GATO)].runner = MSG_GATO;

    perro_config->min_speed = min_perro;
    perro_config->max_speed = max_perro;
    perro_config->destino = MSG_PERRO;
    
    memoria[destinoToInt(MSG_PERRO)].runner = MSG_PERRO;

    conejo_config->min_speed = min_conejo;
    conejo_config->max_speed = max_conejo;
    conejo_config->destino = MSG_CONEJO;

    memoria[destinoToInt(MSG_CONEJO)].runner = MSG_CONEJO;

	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	if (pthread_create (&idHilo, &atributos, funcionAnimal, (void *)perro_config) != 0)
	{
		perror ("No puedo crear thread Perro");
		exit (-1);
	}

    if (pthread_create (&idHilo, &atributos, funcionAnimal, (void *)gato_config) != 0)
	{
		perror ("No puedo crear thread Gato");
		exit (-1);
	}

    if (pthread_create (&idHilo, &atributos, funcionAnimal, (void *) conejo_config) != 0)
	{
		perror ("No puedo crear thread Conejo");
		exit (-1);
	}

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	pthread_mutex_init (&mutex, NULL);
    
	opcion = menu();  

	while(opcion!= SALIR)   
	{
		opcion = menu();
        if (opcion == 1)
        {
            logInfo("Iniciando carrera");
            pthread_mutex_lock(&mutex);
            memoryStatus->run = 1;
            pthread_mutex_unlock(&mutex);
        } 
	} 

	printf("Saliendo");
    shmdt((char *)memoria);
    libero_memoria(memoryId);
    logInfo("Programa terminado y memoria liberada");
	return 0;
}