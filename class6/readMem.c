#include "../shared/framework.h"
#include "def.h"

int main()
{

    logInfo("Iniciando programa escritura memoria");

    int id_memoria, id_semaforo;
    dato *memoria = NULL;
    int i, aleatorio;

    memoria = (dato*)creo_memoria(sizeof(dato) * CANTIDAD, &id_memoria, CLAVE_BASE);
    id_semaforo = creo_semaforo(CANT_SEMAFORO);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    srand(time(NULL));

    while(1) 
    {
        espera_semaforo(id_semaforo, CUAL_SEMAFORO);
        printf("Lote desde memoria: Numero: %d\n", memoria[i].numero);
        for (i = 1; i < CANTIDAD + 1; i++)
        {
            printf("Leido desde memoria: Numero: %d, Letra: %c\n", memoria[i].numero, memoria[i].letra);
        }
        
        logInfo("Memoria leida");
        libero_semaforo_spinner(id_semaforo, CUAL_SEMAFORO, 1);
    }
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}
