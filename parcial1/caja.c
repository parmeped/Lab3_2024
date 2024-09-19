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

    int processHigher20000 = caj_id == CAJ_ID ? 1 : 0;

    FILE *fp;

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
            continue;
        }

        fscanf(fp, ARCHIVO_LINE, &total);
        
        logInfo(print_message);

        if (total > AMOUNT_PROCESS && processHigher20000) 
        {
            logErr("Procesando compra...");
            sprintf(print_message, "Leido total %d por %d", total, CAJ_ID);
            logInfo(print_message);
            borrar_archivo(NOMBRE_ARCHIVO);
            libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_CAJA_MS);
            continue;
        }
    
        logErr("Procesando compra...");
        sprintf(print_message, "Leido total %d por %d", total, CAJ_ID2);
        logInfo(print_message);
        borrar_archivo(NOMBRE_ARCHIVO);
        libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, SLEEP_CAJA_MS);
    }
    return 0;
}