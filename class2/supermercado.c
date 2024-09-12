#include "../shared/funciones.h"
#include "../shared/definiciones.h"

#define INTERVALO_PEDIDOS 2000

void procesar_evento(int id_cola, mensaje msg)
{
    char cadena[100];
    static int cantidad = 0;
    logInfo("test");
    logWarn("test");
    logErr("test");

    printf("Destino %d\n", (int)msg.long_dest);
    printf("Remitente %d\n", (int)msg.int_rte);
    printf("Evento %d\n", (int)msg.int_evento);
    printf("Mensaje %d\n", (int)msg.char_mensaje);

    switch(msg.int_evento)
    {
        case EVT_CONSULTA_STK:
            printf("Consulta stock\n");
            sprintf(cadena, "%d", cantidad);
            enviar_mensaje(id_cola, msg.int_rte, MSG_SUPERMERCADO, EVT_RESPUESTA_STK, cadena);
        break;

        case EVT_SUMA_STK:
            printf("Suma stock\n");
            cantidad++;
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
        recibir_mensajes(id_cola, MSG_SUPERMERCADO, &msg);
        procesar_evento(id_cola, msg);
    }

    return 0;
}