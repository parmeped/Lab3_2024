#include "../shared/funciones.h"
#include "../shared/definiciones.h"

#define INTERVALO_PEDIDOS 2000

void procesar_evento(int id_cola, mensaje msg)
{
    printf("Destino %d\n", (int)msg.long_dest);
    printf("Remitente %d\n", (int)msg.int_rte);
    printf("Evento %d\n", (int)msg.int_evento);
    printf("Mensaje %d\n", (int)msg.char_mensaje);

    switch(msg.int_evento)
    {
        case EVT_RESPUESTA_STK:
            printf("Rta stock\n");
            printf("STOCK %d\n", atoi(msg.char_mensaje));
        break;

        default:
            printf("\n Evento sin definir\n");
        break;
    }
    printLn();
}

int main()
{
    int id_cola;
    mensaje msg;
    id_cola = creo_id_cola_mensajes(CLAVE_BASE);

    while(1)
    {
        enviar_mensaje(id_cola, MSG_SUPERMERCADO, MSG_REPOSITOR, EVT_SUMA_STK, "SUMA UNO");
        enviar_mensaje(id_cola, MSG_SUPERMERCADO, MSG_REPOSITOR, EVT_CONSULTA_STK, "STOCK?");
        recibir_mensajes(id_cola, MSG_REPOSITOR, &msg);
        procesar_evento(id_cola, msg);
        usleep(INTERVALO_PEDIDOS * 1000);
    }
    return 0;
}