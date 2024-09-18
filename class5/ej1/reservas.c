#include "../../shared/framework.h"
#include "def.h"

int main() 
{
    FILE *fp;
    int id_semaforo;
    char print_message[LARGO_MENSAJE];
    char nuevo_filename[LARGO_MENSAJE];

    int lote_reserva = 1;
    int cant_reservas = 0;
    int vuelo = 1;
    char destino[100];
    char nombre[100];

    id_semaforo = creo_semaforo(1);
    logInfo("Iniciando reservas");

    while(1)
    {
        espera_semaforo(id_semaforo, 0);
        fp = abrir_archivo_lectura(FILE_NAME_EJ1);
        if (fp == NULL) 
        {
            sprintf(print_message, "Archivo en uso, esperando por %d milisegundos...", USEGS_SLEEP_RES);
            logWarn(print_message);            
            libero_semaforo_mspinner(id_semaforo, 0, USEGS_SLEEP_RES);
            continue;
        }

        logInfo("Leyendo reservas");
        while (fscanf(fp, "Vuelo:%d,Destino:%99s,Pasajero:%99s\n", &vuelo, destino, nombre) == 3)
        {
            sprintf(print_message, "Vuelo:%d,Destino:%s,Pasajero:%s\n", vuelo, destino, nombre);
            printLnf(print_message);
            cant_reservas++;
        }

        if (cant_reservas > 0) 
        {
            sprintf(nuevo_filename, FILE_NAME_EJ1_RENAME, lote_reserva);
            sprintf(print_message, "Renombrando archivo: %s", nuevo_filename);
            logInfo(print_message);
            renombrar_archivo(FILE_NAME_EJ1, nuevo_filename);
            cant_reservas = 0;
        }
        cerrar_archivo(fp);
        libero_semaforo_mspinner(id_semaforo, 0, USEGS_SLEEP_RES);
    }
    logWarn("Finalizando reservas");
    exit(0);
}