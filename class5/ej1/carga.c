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
        while(vuelo != 0)
        {
            espera_semaforo(id_semaforo, 0);
            fp = abrir_archivo_escritura(FILE_NAME);
            if (fp == NULL) 
            {
                // if file can't be accesses wait for access.
                logErr("Cant access file");
                exit(0);
            }
            sprintf(print_message, "Favor de ingresar vuelo, 0 para salir. (%d-%d)", MIN_VUELO, MAX_VUELO);
            printLnf(print_message);
            scanf("%d", &vuelo);
            
            while (fgetc(stdin) != '\n' && !feof(stdin));

            if (vuelo == 0 || vuelo > MAX_VUELO || vuelo < MIN_VUELO)
            {
                break;   
            }

            printLnf("Favor de ingresar destino");
            scanf("%s", destino);

            printLnf("Favor de ingresar nombre");
            scanf("%s", nombre);
            fprintf(fp, "Vuelo: %d, Destino: %s, Pasajero: %s", vuelo, destino, nombre);
            printSep();
        }
        libero_semaforo_spinner(id_semaforo, 0, SEGS_SLEEP_CARGA);
        cerrar_archivo(fp);        
    }
}
