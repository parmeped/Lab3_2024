#include "shared.c"

int memoryId, statusMemId;

status *getAnimalStatusMemory()
{
    return (status *)creo_memoria(sizeof(status) * RUNNERS_AMOUNT, &memoryId, CLAVE_BASE);
}

sprintStatus *getStatusMemory()
{
    return (sprintStatus*)creo_memoria(sizeof(sprintStatus), &statusMemId, CLAVE_BASE_2);
}


void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	printf("Remitente %s esta corriendo!\n", intToDestino(msg.int_rte));
	printf("RemitenteInt: %d\n", msg.int_rte);
	
	status *memoria = (status *)getAnimalStatusMemory();
    sprintStatus *memoriaStatus = (sprintStatus*)getStatusMemory();

	switch (msg.int_evento)
	{
		case EVT_CORRO:			
			printf("Pasos: %d\n", memoria[intToDestino(msg.int_rte)].totalSteps);
			printf("Cantidad de pasos: %d\n", memoria[intToDestino(msg.int_rte)].totalSteps);

			if (memoria[intToDestino(msg.int_rte)].totalSteps >= max_pasos)
			{
				int winnerAmountOfSteps = memoria[intToDestino(msg.int_rte)].amountOfSteps;
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
			break;			
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
	int 	id_cola_mensajes;
	int		i;	

	mensaje	msg;	
	status *memoria = (status *)getAnimalStatusMemory();
    sprintStatus *memoriaStatus = (sprintStatus*)getStatusMemory();

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
		procesar_evento(id_cola_mensajes, msg);
	};

	shmdt((char *)memoria);
    libero_memoria(memoryId);
	shmdt((char *)memoriaStatus);
	libero_memoria(statusMemId);
    logInfo("Programa terminado y memoria liberada");
	
	return 0;
}