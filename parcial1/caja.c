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
    int array_size_compras = array_size_productos;

    Compra compras[array_size_productos];
    Compras comprasTotal;
    
    memcpy(comprasTotal.compras, compras, sizeof compras);

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

        fread(&comprasTotal, sizeof(Compras), 1, fp);
        
        logInfo(print_message);
        memcpy(comprasTotal.compras, compras, sizeof compras);

        if (comprasTotal.total >= AMOUNT_PROCESS && caj_id == CAJ_ID) 
        {
            logWarn("Procesando compra...");
            for (int i = 0; i < array_size_compras; i++)
            {
                sprintf(print_message, "Producto: %s, Cantidad: %d, Importe: %d", productos[compras[i].id - 1].descripcion, compras[i].cantidad, compras[i].cantidad * productos[compras[i].id - 1].importe);
                logInfo(print_message);
                // reset
                compras[i].cantidad = 0;
            }

            sprintf(print_message, "Leido total %d por %d", comprasTotal.total, caj_id);
            logInfo(print_message);
            borrar_archivo(NOMBRE_ARCHIVO);
            libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_CAJA_MS);
            continue;
        }
        
        if (comprasTotal.total < AMOUNT_PROCESS && caj_id == CAJ_ID2)
        {
            logWarn("Procesando compra...");
            for (int i = 0; i < array_size_compras; i++)
            {
                sprintf(print_message, "Producto: %s, Cantidad: %d, Importe: %d", productos[compras[i].id - 1].descripcion, compras[i].cantidad, compras[i].cantidad * productos[compras[i].id - 1].importe);
                logInfo(print_message);
                // reset
                compras[i].cantidad = 0;
            }

            sprintf(print_message, "Leido total %d por %d", comprasTotal.total, caj_id);
            logInfo(print_message);
            borrar_archivo(NOMBRE_ARCHIVO);
            libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_CAJA_MS);
            continue;
        }
    }
    return 0;
}