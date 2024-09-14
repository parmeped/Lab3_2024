#include "../shared/framework.h"
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

            while (vuelo < MIN_VUELO && vuelo > MAX_VUELO)
            {
                sprintf(info, "Favor de ingresar vuelo (%d-%d)", MIN_VUELO, MAX_VUELO);
                printf(info);
                scanf("%d", vuelo);
            }
            printf("Favor de ingresar destino");
            scanf("%s", destino);

            printf("Favor de ingresar nombre");
            scanf("%s", nombre);
        }
    }

}
