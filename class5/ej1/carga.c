#include "../../shared/framework.h"
#include "def.h"

int main()
{
    FILE *fp;
    int id_semaforo;
    char info[LARGO_MENSAJE];

    int vuelo = 1;
    char destino[100];
    char nombre[100];

    id_semaforo = creo_semaforo(1);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    while(1)
    {
        espera_semaforo(id_semaforo, 0);

        while (vuelo != 0) 
        {
            fp = abrir_archivo_escritura(FILE_NAME);
            if (fp == NULL) 
            {
                // if file can't be accesses wait for access.
                logErr("Cant access file");
                exit(0);
            }

            while ((vuelo < MIN_VUELO && vuelo > MAX_VUELO) || vuelo == 0)
            {
                printf("Favor de ingresar vuelo (%d-%d)", MIN_VUELO, MAX_VUELO);
                scanf("%d", vuelo);
            }
            printf("Favor de ingresar destino");
            scanf("%s", destino);

            print("Favor de ingresar nombre");
            scanf("%s", nombre);
            fprintf(fp, "Vuelo: %d, Destino: %s, Pasajero: %s", vuelo, destino, nombre);

        }
        libero_semaforo(id_semaforo, 0);
        cerrar_archivo(fp);
        logInfo("Fin Programa");
    }
}
