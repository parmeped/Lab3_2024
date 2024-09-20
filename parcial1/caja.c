#include "../shared/framework.h"
#include "def.h"

int main(int argc, char *argv[])
{
    char print_message[LARGO_MENSAJE];
    
    int caj_id = atoi(argv[1]);
    if (caj_id != CAJ_ID && caj_id != CAJ_ID2) 
    {
        sprintf(print_message, "Id invalido, debe ser %d o %d", CAJ_ID, CAJ_ID2);
        logInfo(print_message);
        return 1;
    }

    if (caj_id == CAJ_ID) 
    {
        logInfo("Proceso compras mayores a 20000");
    }
    else 
    {
        logInfo("No proceso compras mayores a 20000");
    }

    FILE *fp;
    int array_size_productos = ARRAY_SIZE(productos);
    Compra compras[array_size_productos];
    int array_size_compras = array_size_productos;

    for (int i = 0; i < array_size_productos; i++)
    {
        compras[i].id = productos[i].id;
        compras[i].cantidad = 0;
    }

    int id_semaforo = creo_semaforo(SEM_AMOUNT);
    char nombre_archivo[100];
    int total = 0;

    while(1) 
    {
        espera_semaforo(id_semaforo, SEM_NUMBER);
        
        sprintf(print_message, "Procesando compra en caja %d", caj_id);
        logInfo(print_message);

        fp = abrir_archivo_lectura(NOMBRE_ARCHIVO);
        if (fp == NULL) 
        {
            logErr("No se pudo abrir archivo para lectura");
            libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_CAJA_MS);
            continue;
        }

        fread(compras, sizeof(Compra), array_size_compras, fp);
        
        logInfo(print_message);

        // esto deberia ser AMOUNT_PROCESS pero por algun motivo no me lo toma correctamente y entra en el otro.
        if (total >= 20000 && caj_id == CAJ_ID) 
        {
            logWarn("Procesando compra...");
            for (int i = 0; i < array_size_compras; i++)
            {
                sprintf(print_message, "Producto: %s, Cantidad: %d, Importe: %d", productos[compras[i].id - 1].descripcion, compras[i].cantidad, compras[i].cantidad * productos[compras[i].id - 1].importe);
                logInfo(print_message);
                total += compras[i].cantidad * productos[compras[i].id - 1].importe;
                // reset
                compras[i].cantidad = 0;
            }

            sprintf(print_message, "Leido total %d por %d", total, caj_id);
            logInfo(print_message);
            borrar_archivo(NOMBRE_ARCHIVO);
            libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_CAJA_MS);
            continue;
        }
        
        if (total < 20000 && caj_id == CAJ_ID2)
        {
            logWarn("Procesando compra...");
            logWarn("Procesando compra...");
            for (int i = 0; i < array_size_compras; i++)
            {
                sprintf(print_message, "Producto: %s, Cantidad: %d, Importe: %d", productos[compras[i].id - 1].descripcion, compras[i].cantidad, compras[i].cantidad * productos[compras[i].id - 1].importe);
                logInfo(print_message);
                total += compras[i].cantidad * productos[compras[i].id - 1].importe;
                // reset
                compras[i].cantidad = 0;
            }

            sprintf(print_message, "Leido total %d por %d", total, caj_id);
            logInfo(print_message);
            borrar_archivo(NOMBRE_ARCHIVO);
            libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_CAJA_MS);
            continue;
        }
    }
    return 0;
}