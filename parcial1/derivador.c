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

    int id_semaforo;
    char print_message[LARGO_MENSAJE];
    char nombre_archivo[100];
    int total = 0;
    int id_producto = -1;
    int cantidad;
    
    int array_size_productos = ARRAY_SIZE(productos);
    int array_size_compras = ARRAY_SIZE(compras);

    for (int i = 0; i < array_size_productos; i++)
    {
        compras[i].id = productos[i].id;
        compras[i].cantidad = 0;
    }

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
        
        id_producto = -1;
        total = 0;
        while(id_producto != DERIVADOR_EXIT)
        {
            printSep();

            logInfo("Productos disponibles:");
            for (int i = 0; i < array_size_productos; i++)
            {
                sprintf(print_message, "Producto: %s, Id: %d, precio: %d", productos[i].descripcion, productos[i].id, productos[i].importe);
                logInfo(print_message);
            }
            sprintf(print_message, "Total en productos: %d", total);
            logInfo(print_message);
            
            sprintf(print_message, "Ingrese Id producto, %d para salir", DERIVADOR_EXIT);
            logInfo(print_message);
            scanf("%d", &id_producto);

            if (id_producto == DERIVADOR_EXIT) 
            {
                logInfo("Finalizando ingreso productos");
                break;
            }

            // asumimos los prods estan ordenados, sino habria q buscar el min y max...
            if (id_producto < productos[0].id || id_producto > productos[array_size_productos - 1].id) 
            {
                logWarn("Producto no encontrado");
                continue;
            }

            sprintf(print_message, "Ingresar cantidad del producto elegido: %s", productos[id_producto - 1].descripcion);
            logInfo(print_message);
            scanf("%d", &cantidad);

            if (cantidad <= 0) 
            {
                logWarn("Cantidad invalida, ingresar mayor a 0");
                continue;
            }

            compras[id_producto - 1].cantidad += cantidad;
            total += compras[id_producto - 1].cantidad * productos[id_producto - 1].importe;
        }

        logInfo("Productos adquiridos:");
        for (int i = 0; i < array_size_compras; i++)
        {
            sprintf(print_message, "Producto: %s, Cantidad: %d", productos[compras[i].id - 1].descripcion, compras[i].cantidad);    
            logInfo(print_message);
            // reset
            compras[i].cantidad = 0;
        }

        sprintf(print_message, "Total productos: %d", total);
        logInfo(print_message);

        fprintf(fp, ARCHIVO_LINE, total);        
        cerrar_archivo(fp);
        libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_DERIVADOR_MS);
    }
    return 0;
}