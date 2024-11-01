#include "sharedE.c"

int memoryId, statusMemId;

runnerStats *getRunnersStatusMemory()
{
    return (runnerStats *)creo_memoria(sizeof(runnerStats) * runners_amount, &memoryId, CLAVE_BASE);
}

sprintStatus *getStatusMemory()
{
    return (sprintStatus*)creo_memoria(sizeof(sprintStatus), &statusMemId, CLAVE_BASE_2);
}

int menu(void)
{
    int opcion;

    printf("Menu\n\n");
    printf("1.\tPresionar 1 para empezar\n\n");
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
	int 	id_cola_mensajes;
	int		i, opcion, turno = 1;	
	int 	mosquitos = amount_mosquitos;

	mensaje	msg;	
	runnerStats *memoria = (runnerStats *)getRunnersStatusMemory();
    sprintStatus *memoriaStatus = (sprintStatus*)getStatusMemory();

	int cantidad = 0;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes);

	opcion = menu();  	

	if (opcion == 1) 
	{
		printf("opcion: %d\n", opcion);
		memoriaStatus->run = 1;
	}

	while(memoriaStatus->run == 0)
	{
		logInfo("Esperando inicio carrera");
		spinner(1);
	}


	logInfo("Iniciando Carrera");
	while(memoriaStatus->run == 1)
	{
		printf("mosquitos: %d\n", mosquitos);

		if (mosquitos <= 0) 
		{
			logWarn("Gano el humo!");
			memoriaStatus->run = 0;
			break;
		}

		logInfof("Iniciando turno %d", turno++);
		for (i = 0; i < runners_amount; i++)
		{
			if (memoria[i].alive == 0)
			{
				printf("enviando a %d", memoria[i].runner);
				enviar_mensaje(id_cola_mensajes, memoria[i].runner, MSG_POINTER, EVT_CORRO, "");
			}
		}
		mSpinner(turn_duration);

		printf("steps humo:", memoria[MSG_SMOKE].totalSteps);
		printf("steps mosquito1:", memoria[MSG_MOSQUITO1].totalSteps);
		printf("steps mosquito2:", memoria[MSG_MOSQUITO2].totalSteps);
		
		if (memoria[MSG_SMOKE].totalSteps >= memoria[MSG_MOSQUITO1].totalSteps)
		{
			enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO1, MSG_POINTER, EVT_FIN, "");
			mosquitos--;
		}

		if (memoria[MSG_SMOKE].totalSteps >= memoria[MSG_MOSQUITO2].totalSteps)
		{
			enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO2, MSG_POINTER, EVT_FIN, "");
			mosquitos--;
		}

		if (memoria[MSG_MOSQUITO1].totalSteps >= finish_line)
		{			
			enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO1, MSG_POINTER, EVT_SOBREVIVIO, "");
			mosquitos--;
		}

		if (memoria[MSG_MOSQUITO2].totalSteps >= finish_line)
		{			
			enviar_mensaje(id_cola_mensajes, MSG_MOSQUITO2, MSG_POINTER, EVT_SOBREVIVIO, "");
			mosquitos--;
		}
	};

	shmdt((char *)memoria);
    libero_memoria(memoryId);
	shmdt((char *)memoriaStatus);
	libero_memoria(statusMemId);
    logInfo("Programa terminado y memoria liberada");
	
	return 0;
}