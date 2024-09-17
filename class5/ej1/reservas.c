#include "../../shared/framework.h"
#include "def.h"

int main() 
{
    FILE *fp;
    int id_semaforo;
    char print_message[LARGO_MENSAJE];
    char nuevo_filename[LARGO_MENSAJE];

    int lote_reserva = 1;
    int vuelo = 1;
    char destino[100];
    char nombre[100];

    id_semaforo = creo_semaforo();

    while(1)
    {
        espera_semaforo(id_semaforo, 0);
        fp = abrir_archivo_lectura(FILE_NAME_EJ1);
        if (fp == NULL) 
        {
            sprintf(print_message, "Archivo en uso, esperando por %d segundos...", SEGS_SLEEP_RES);
            logErr(print_message);
            cerrar_archivo(fp);
            libero_semaforo_spinner(id_semaforo, 0, SEGS_SLEEP_CARGA);
            continue;
        }

        while (!feof(fp))
        {
            fscanf(fp, "%s", print_message);
            printLnf(print_message);
        }
        
        sprintf(nuevo_filename, FILE_NAME_EJ1_RENAME, lote_reserva);
        renombrar_archivo(FILE_NAME_EJ1, nuevo_filename);
        cerrar_archivo(fp);
        libero_semaforo_spinner(id_semaforo, 0, SEGS_SLEEP_CARGA);
    }
}