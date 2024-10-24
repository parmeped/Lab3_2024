#include "def.h"
#include "../shared/framework.h"

void procesar_evento(int id_cola_mensajes, mensaje msg)
{
	char 	cadena[LARGO_TMENSAJE];
	int 	count = 0;
	int	cliente=0;
	int 	importe=0;
	char 	*token;
	int	i;

	printf("Destino   %d\n", (int) msg.long_dest);
	printf("Remitente %d\n", msg.int_rte);
	printf("Evento    %d\n", msg.int_evento);
	printf("Mensaje   %s\n", msg.char_mensaje);
	switch (msg.int_evento)
	{
		case EVT_CORRO:
			printf("Alguien corriendo\n");
		break;	
		case EVT_FIN:
			logInfo("Finalizado!\n");
		break;
		case EVT_NINGUNO:
			printf("Ninguno?\n");
		break;
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
	
	int cantidad = 0;
	
	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);

	borrar_mensajes(id_cola_mensajes); //Borra todos los mensajes que haya en la cola.

	while(1)
	{
		recibir_mensajes(id_cola_mensajes, MSG_TABLERO, &msg);
		procesar_evento(id_cola_mensajes, msg);
	};
	
	return 0;
}