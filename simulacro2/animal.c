#include "def.h"
#include <pthread.h>
#include "../shared/framework.h"

int id_cola_mensajes;
pthread_mutex_t mutex;

#define SALIR			0

void *funcionPerro(void *parametro)
{
	mensaje	msg;
	printf ("ThreadPerro\n");
	while(1)
	{
		recibir_mensajes(id_cola_mensajes, MSG_JUGADOR1, &msg);
		pthread_mutex_lock (&mutex);
				procesar_evento(msg);
		pthread_mutex_unlock (&mutex);	
	};
	printf ("Hijo  : Termino\n");
	pthread_exit ((void *)"Listo");
}

void *funcionGato(void *parametro)
{
	mensaje	msg;
	printf ("ThreadGato\n");
	while(1)
	{
		recibir_mensajes(id_cola_mensajes, MSG_JUGADOR2, &msg);
		pthread_mutex_lock (&mutex);
				procesar_evento(msg);
		pthread_mutex_unlock (&mutex);	
	};
	printf ("Hijo  : Termino\n");
	pthread_exit ((void *)"Listo");
}

void *funcionConejo(void *parametro)
{
	mensaje	msg;
	printf ("ThreadConejo\n");
	while(1)
	{
		recibir_mensajes(id_cola_mensajes, MSG_JUGADOR3, &msg);
		pthread_mutex_lock (&mutex);
				procesar_evento(msg);
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
    printf("Elija opcion: ");
    fflush(stdin);  
    while((scanf(" %d", &opcion) != 1)
          || (opcion < 0))    
    {
      fflush(stdin);                 
      printf("No valido\n\n");
      printf("Elija opcion: ");
    }
    return opcion;
}

int main()
{
	int 			opcion;    
	int 			id_memoria_codigos;
	mensaje			msg;
	int 			codigo;
	int				cantidad;
	char 			cadena[LARGO_TMENSAJE];

	pthread_t 		idHilo;
	pthread_attr_t 	atributos;

	
	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	if (pthread_create (&idHilo, &atributos, funcionPerro, NULL)!= 0)
	{
		perror ("No puedo crear thread Perro");
		exit (-1);
	}

    if (pthread_create (&idHilo, &atributos, funcionGato, NULL)!= 0)
	{
		perror ("No puedo crear thread Gato");
		exit (-1);
	}

    if (pthread_create (&idHilo, &atributos, funcionConejo, NULL)!= 0)
	{
		perror ("No puedo crear thread Conejo");
		exit (-1);
	}

	id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
	
	pthread_mutex_init (&mutex, NULL);
	
	opcion = menu();  

	while(opcion!= SALIR)   
	{
		opcion = menu(); 
	}
	printf("Saliendo");
	return 0;
}