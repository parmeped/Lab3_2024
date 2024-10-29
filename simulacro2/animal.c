#include <pthread.h>
#include "def.h"
#include "../shared/framework.h"

int id_cola_mensajes;
pthread_mutex_t mutex;

#define SALIR			0


const char* destinoToString(Destinos destino) {
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

void generar_evento(Destinos remitente, int cantidad_pasos, int pasos) 
{
    mensaje msg;
    msg.long_dest = remitente;
    msg.int_rte = 0;
    if (pasos >= max_pasos)
    {
        msg.int_evento = EVT_FIN;
    }
    else
    {
        msg.int_evento = EVT_CORRO;
    }
    printf("Generando evento %d\n", msg.int_evento);    
    printf("Cantidad de pasos %d\n", cantidad_pasos);
    printf("Pasos %d\n", pasos);
    enviar_mensaje(id_cola_mensajes, MSG_TABLERO, remitente, msg.int_evento, "");
    spinner(1);
}

void *funcionAnimal(void *input)
{
	mensaje	msg;
    int cantidad_pasos = 0;
    int pasos = 0;
	while(1)
	{
    	printf ("Thread: %s\n", destinoToString(((struct animal_config*)input)->destino));
		pthread_mutex_lock (&mutex);
                pasos += randomNumber(((struct animal_config*)input)->min_speed, ((struct animal_config*)input)->max_speed);
                cantidad_pasos++;
                generar_evento(((struct animal_config*)input)->destino, cantidad_pasos, pasos);
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

	struct animal_config gato_config = {
    .min_speed = min_gato,
    .max_speed = max_gato,
    .destino = MSG_GATO
    };

    struct animal_config perro_config = {
        .min_speed = min_perro,
        .max_speed = max_perro,
        .destino = MSG_PERRO
    };

    struct animal_config conejo_config = {
        .min_speed = min_conejo,
        .max_speed = max_conejo,
        .destino = MSG_CONEJO
    };

	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	if (pthread_create (&idHilo, &atributos, funcionAnimal, NULL != 0)
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
	}
	printf("Saliendo");
	return 0;
}