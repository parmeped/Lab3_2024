#include "../../shared/framework.h"
#include "def.h"

int main()
{
    FILE *fp;
    int id_semaforo;
    char print_message[LARGO_MENSAJE];

    int vuelo = 1;
    char destino[100];
    char nombre[100];

    id_semaforo = creo_semaforo(1);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    while(1)
    {
        espera_semaforo(id_semaforo, 0);
        fp = append_archivo(FILE_NAME_EJ1);

        while(vuelo != 0)
        {
            if (fp == NULL) 
            {
                // if file can't be accesses wait for access.
                sprintf(print_message, "Archivo en uso, esperando por %d segundos...", SEGS_SLEEP_CARGA);
                logErr(print_message);
                break;
            }

            sprintf(print_message, "Favor de ingresar vuelo, 0 para salir. (%d-%d)", MIN_VUELO, MAX_VUELO);
            printLnf(print_message);
            scanf("%d", &vuelo);
            
            while (fgetc(stdin) != '\n' && !feof(stdin));

            if (vuelo == 0)
            {
                printLnf("Cerrando lote");
                vuelo = -1;
                break;
            }

            if (vuelo > MAX_VUELO || vuelo < MIN_VUELO)
            {
                sprintf(print_message, "Se ingresó un vuelo invalido (%d)", vuelo);
                printLnf(print_message);
                continue;
            }

            printLnf("Favor de ingresar destino");
            scanf("%s", destino);

            printLnf("Favor de ingresar nombre");
            scanf("%s", nombre);
            fprintf(fp, "Vuelo: %d, Destino: %s, Pasajero: %s\n", vuelo, destino, nombre);
            printSep();
        }
        cerrar_archivo(fp);
        libero_semaforo_spinner(id_semaforo, 0, SEGS_SLEEP_CARGA);
    }
    exit(0);
}
