#include "sharedE.c"
#include <pthread.h>

int id_cola_mensajes;
pthread_mutex_t mutex;
int runnerMemId, statusMemId;

#define SALIR			0

runnerStats *getRunnersStatusMemory()
{
    return (runnerStats *)creo_memoria(sizeof(runnerStats) * runners_amount, &runnerMemId, CLAVE_BASE);
}

sprintStatus *getStatusMemory()
{
    return (sprintStatus*)creo_memoria(sizeof(sprintStatus), &statusMemId, CLAVE_BASE_2);
}

void run(int steps, Destiny destiny) 
{
    runnerStats *memoria = (runnerStats *)getRunnersStatusMemory();
    printf("Sumando pasos - Pasos: %d", steps);
    memoria[destiny].totalSteps = steps;
}

void die(Destiny destiny)
{
    runnerStats *memoria = (runnerStats *)getRunnersStatusMemory();
    logInfof("Famosas ultimas palabras del pobre mosquito: Squaaaaaaaashhhhhhhh %s!!", destinoToString(destiny));
    memoria[destiny].alive = -1;
}

void finish(Destiny destiny)
{
    runnerStats *memoria = (runnerStats *)getRunnersStatusMemory();
    logInfof("Finalizado %s!!", destinoToString(destiny));
    memoria[destiny].finished = 1;
}

// estos eventos los procesa tanto el humo como los mosquitos. idealmente esta funcion se pasaria tambien de acuerdo a cual es el actor, para que tengan su propia implementacion de
// acuerdo a cada uno. o, con polimorfismo cada uno implementa sus funciones die(), run(), etc
void processEvent(int id_cola_mensajes, mensaje msg, int pasos)
{
	printf("Remitente %s esta corriendo!\n", intToDestinoString(msg.int_rte));
	
	runnerStats *memoria = (runnerStats *)getRunnersStatusMemory();
    sprintStatus *memoriaStatus = (sprintStatus*)getStatusMemory();

	switch (msg.int_evento)
	{
		case EVT_CORRO:			
			run(pasos, msg.int_rte);
			break;			
		case EVT_FIN:
            die(msg.int_rte);
            break;
        case EVT_SOBREVIVIO:
            finish(msg.int_rte);
            break;
		case EVT_NINGUNO:
		default:
			printf("\nEvento sin definir\n");
		break;
	}
	printSep();
}

void *runnerFunction(void *input)
{
	mensaje	msg;
    int pasos = 0;
    sprintStatus *memoriaStatus = (sprintStatus *) getStatusMemory();
	runnerStats *memoria = (runnerStats *) getRunnersStatusMemory();

    int memPos = ((struct runner_config*)input)->runner;
    memoria[memPos].alive = 1;
    memoria[memPos].finished = 0;

    while(memoriaStatus->run == 0)
	{
		logInfof("Esperando inicio carrera supervivencia, Thread: %s", destinoToString(((struct runner_config*)input)->runner));
		spinner(spinner_inicio);
	}
    
    // and still alive!
    while(memoriaStatus->run == 1 && memoria[memPos].alive == 1 && memoria[memPos].finished == 0)
	{
    	printf("Thread: %s\n", destinoToString(((struct runner_config*)input)->runner));
        printf("MinSpeed: %d, MaxSpeed: %d\n", ((struct runner_config*)input)->min_speed, ((struct runner_config*)input)->max_speed);
        recibir_mensajes(id_cola_mensajes, MSG_POINTER, &msg);
		pthread_mutex_lock (&mutex);
            pasos += randomNumber(((struct runner_config*)input)->min_speed, ((struct runner_config*)input)->max_speed);
            processEvent(id_cola_mensajes, msg, pasos);
        pthread_mutex_unlock (&mutex);
	};
	printf ("Hijo  : Termino\n");
	pthread_exit ((void *)"Listo");
}

int main()
{
	pthread_t 		idHilo;
	pthread_attr_t 	atributos;
    int opcion;
    
    runnerStats *memoria = (runnerStats *)getRunnersStatusMemory();
    sprintStatus *memoriaStatus = (sprintStatus *) getStatusMemory();

    // ----- configs: idealmente esto iria en otra func.
	struct runner_config *mosquito1 = (struct runner_config *)malloc(sizeof(struct runner_config));
    struct runner_config *mosquito2 = (struct runner_config *)malloc(sizeof(struct runner_config));
    struct runner_config *smoke = (struct runner_config *)malloc(sizeof(struct runner_config));

    mosquito1->min_speed = min_mosquito;
    mosquito1->max_speed = max_mosquito;
    mosquito1->runner = MSG_MOSQUITO1;

    memoria[MSG_MOSQUITO1].runner = MSG_MOSQUITO1;

    mosquito2->min_speed = min_mosquito;
    mosquito2->max_speed = max_mosquito;
    mosquito2->runner = MSG_MOSQUITO2;
    
    memoria[MSG_MOSQUITO2].runner = MSG_MOSQUITO2;

    smoke->min_speed = min_smoke;
    smoke->max_speed = max_smoke;
    smoke->runner = MSG_SMOKE;

    memoria[MSG_SMOKE].runner = MSG_SMOKE;

	pthread_attr_init (&atributos);
	pthread_attr_setdetachstate (&atributos, PTHREAD_CREATE_JOINABLE);
	if (pthread_create (&idHilo, &atributos, runnerFunction, (void *)mosquito1) != 0)
	{
		perror ("No puedo crear thread Mosquito1");
		exit (-1);
	}

    if (pthread_create (&idHilo, &atributos, runnerFunction, (void *)mosquito2) != 0)
	{
		perror ("No puedo crear thread Mosquito2");
		exit (-1);
	}

    if (pthread_create (&idHilo, &atributos, runnerFunction, (void *) smoke) != 0)
	{
		perror ("No puedo crear thread Humo");
		exit (-1);
	}
    // --------- fin configs

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	
	pthread_mutex_init (&mutex, NULL);
    
	while(memoriaStatus->run == 0)
    {
        logInfo("Esperando inicio carrera");
        spinner(1);
    }

    while(memoriaStatus->run != 0)
    {
        logInfo("Esperando fin carrera");
        spinner(1);
    }

	printf("Saliendo");
    shmdt((char *)memoria);
    libero_memoria(runnerMemId);
    shmdt((char *)statusMemId);
    libero_memoria(statusMemId);
    logInfo("Programa terminado y memoria liberada");
	return 0;
}