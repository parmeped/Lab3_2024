#include "def.h"
#include "../shared/framework.h"

int statusMemId;
// Tablero keeps a tab on how everyones doing, when someone wins they print message and send STOP to everyone. 
// Array should be kept on memory..? 
void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	printf("Remitente %d\n", msg.int_rte);
	switch (msg.int_evento)
	{
		case EVT_CORRO:
			printf("Alguien corriendo\n");
			
		case EVT_NINGUNO:
		case EVT_FIN:
		default:
			printf("\nEvento sin definir\n");
		break;
	}
	printf("------------------------------\n");	
}
		
// to start both processes need to be up and running and communicate through a key. 
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

	borrar_mensajes(id_cola_mensajes); //Borra todos los mensajes que haya en la cola.
	logInfo("Esperando inicio carrera");
	while(memoriaStatus->run == 1)
	{
		recibir_mensajes(id_cola_mensajes, MSG_TABLERO, &msg);
		procesar_evento(id_cola_mensajes, msg);
	};

	shmdt((char *)memoria);
    libero_memoria(memoryId);
	libero_memoria(statusMemId);
    logInfo("Programa terminado y memoria liberada");
	
	return 0;
}