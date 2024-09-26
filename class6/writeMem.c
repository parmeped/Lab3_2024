#include "../shared/framework.h"
#include "def.h"

#include <signal.h>

volatile sig_atomic_t stop;

void handle_sigint(int sig) {
    stop = 1;
}

int main()
{
    signal(SIGINT, handle_sigint);

    logInfo("Iniciando programa lectura memoria");

    int id_memoria, id_semaforo;
    dato *memoria = NULL;
    int lote = 0;
    int i, aleatorio = 0;

    memoria = (dato*)creo_memoria(sizeof(dato) * CANTIDAD, &id_memoria, CLAVE_BASE);
    id_semaforo = creo_semaforo(CANT_SEMAFORO);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    srand(time(NULL));

    while(!stop) 
    {
        espera_semaforo(id_semaforo, CUAL_SEMAFORO);
        memoria[0].numero = lote++;
        for (i = 1; i < CANTIDAD + 1; i++)
        {
            aleatorio = randomNumberPrevSeed(1, 100, aleatorio);
            memoria[i].numero = aleatorio;
            memoria[i].letra = (char)aleatorio;
            printf("Numero: %d, Letra: %c\n", memoria[i].numero, memoria[i].letra);
        }
        
        logInfo("Memoria escrita");
        libero_semaforo_spinner(id_semaforo, CUAL_SEMAFORO, TIEMPO_SLEEP);
    }

    logInfo("Liberando memoria");
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    return 0;
}