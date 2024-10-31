#include "def.h"
#include "../shared/framework.h"

int statusMemId;

const int destinoToInt(Destinos destino) 
{
    switch (destino) 
    {
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

const char* destinoToString(Destinos destino) 
{
    switch (destino) 
    {
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


void procesar_evento(int id_cola_mensajes, mensaje msg, status *memoria, sprintStatus *memoriaStatus)
{
	printf("Remitente %d\n", msg.int_rte);
	switch (msg.int_evento)
	{
		case EVT_CORRO:
			printf("Alguien corriendo\n");
			if (memoria[destinoToInt(msg.long_dest)].totalSteps >= max_pasos)
			{
				int winnerAmountOfSteps = memoria[destinoToInt(msg.long_dest)].amountOfSteps;
				for (int i = 0; i < RUNNERS_AMOUNT; i++)
				{
					if (memoria[i].amountOfSteps == winnerAmountOfSteps && memoria[i].totalSteps >= max_pasos)
					{
						// print ganadores. se podria hacer un if para mostrar si hubo mas de un ganador y entonces mostrar "Ganadores"
						logInfof("Ganador %s\n", destinoToString(memoria[i].runner));
					}
				}
				memoriaStatus->run = 0;				
			}			
		case EVT_NINGUNO:
		case EVT_FIN:
		default:
			printf("\nEvento sin definir\n");
		break;
	}
	printf("------------------------------\n");	
}
		
int main()
{
	int 	id_cola_mensajes, memoryId;
	int		i;	

	mensaje	msg;
	status *memoria = NULL;
	memoria = (status*)creo_memoria(sizeof(status) * RUNNERS_AMOUNT, &memoryId, CLAVE_BASE);
    sprintStatus *memoriaStatus = NULL;
    memoriaStatus = (sprintStatus*)creo_memoria(sizeof(sprintStatus), &statusMemId, CLAVE_BASE_2);

	int cantidad = 0;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);
	while(memoriaStatus->run == 0)
	{
		logInfo("Esperando inicio carrera");
		spinner(1);
	}

	logInfo("Iniciando Carrera");
	while(memoriaStatus->run == 1)
	{
		recibir_mensajes(id_cola_mensajes, MSG_TABLERO, &msg);
		procesar_evento(id_cola_mensajes, msg, memoria, memoriaStatus);
	};

	shmdt((char *)memoria);
    libero_memoria(memoryId);
	libero_memoria(statusMemId);
    logInfo("Programa terminado y memoria liberada");
	
	return 0;
}