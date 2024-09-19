#include "../shared/framework.h"
#include "def.h"

// hago print de productos
// espero semaforo
// ingreso por teclado productos
// al finalizar ingreso, guardo en archivo
// guardo en file solo el total.
// levanto semaforo
// caja 1 o 2 procesan acorde, borran archivo una vez procesado

// Step1: solo guardar el importe total de la compra en el archivo. Procesarlo en derivador
// Step2: guardar la compra entera en el archivo, levantar en las cajas y procesar ahi.

int main()
{

    logInfo("Iniciando programa derivador");

    Compra compras[10];
    FILE *fp;

    for (int i = 0; i < sizeof(productos); i++)
    {
        compras[i] = struct Compra = { .id = productos[i].id, .cantidad = 0};
    }

    int id_semaforo;
    char print_message[LARGO_MENSAJE];
    char nombre_archivo[100];
    int total = 0;
    int id_producto = -1;
    int cantidad;

    id_semaforo = creo_semaforo(SEM_AMOUNT);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    while(1) 
    {
        espera_semaforo(id_semaforo, SEM_NUMBER);
        fp = abrir_archivo_escritura(NOMBRE_ARCHIVO);
        if (fp == NULL) 
        {
            logErr("No se pudo abrir archivo para escritura");
            exit(1);
        }
        
        while(id_producto != DERIVADOR_EXIT) 
        {
            printSep();
            logInfo("Productos disponibles:");
            for (int i = 0; i < sizeof(productos); i++)
            {
                sprintf(print_message, "Producto: %s, Id: %d", productos[i].descripcion, productos[i].id);
                logInfo(print_message);
            }
            
            sprintf(print_message, "Ingrese Id producto, %d para salir", DERIVADOR_EXIT);
            logInfo(print_message);
            scanf("%d", &id_producto);

            if (id_producto == DERIVADOR_EXIT) 
            {
                logInfo("Finalizando ingreso productos");
                id_producto = -1;
                break;
            }

            // asumimos los prods estan ordenados, sino habria q buscar el min y max...
            if (id_producto < productos[0].id || id_producto > productos[sizeof(productos) - 1].id) 
            {
                logWarn("Producto no encontrado");
                id_producto = -1;
                continue;
            }

            sprintf(print_message, "Ingresar cantidad del producto elegido: %s", productos[id_producto - 1].descripcion);
            logInfo(print_message);
            scanf("%d", &cantidad);

            if (atoi(&cantidad) <= 0) 
            {
                logWarn("Cantidad invalida.");
                id_producto = -1;
                continue;
            }

            compras[id_producto - 1].cantidad += cantidad;
        }

        logInfo("Productos adquiridos:");
        for (int i = 0; i < sizeof(compras); i++)
        {
            sprintf(print_message, "Producto: %s, Cantidad: %d", productos[compras[i].id - 1].descripcion, compras[i].cantidad);    
            logInfo(print_message);
            total += compras[i].cantidad * productos[i].importe;
        }

        sprintf(print_message, "Total productos: %d", total);
        logInfo(print_message);

        fprintf(fp, "Total: %d\n", total);
        cerrar_archivo(fp);
        libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_DERIVADOR_MS);
    }
}