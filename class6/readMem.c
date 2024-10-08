#include "../shared/framework.h"
#include "def.h"

#include <signal.h>

volatile sig_atomic_t stop;

void handle_sigint(int sig) {
    stop = 1;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, handle_sigint);

    logInfo("Iniciando programa escritura memoria");

    int id_memoria, id_semaforo;
    dato *memoria = NULL;
    int i, aleatorio;

    memoria = (dato*)creo_memoria(sizeof(dato) * CANTIDAD, &id_memoria, CLAVE_BASE);
    id_semaforo = creo_semaforo(CANT_SEMAFORO);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    srand(time(NULL));

    while(!stop) {
        espera_semaforo(id_semaforo, CUAL_SEMAFORO);
        logInfo("Leyendo memoria");

        for (i = 0; i < CANTIDAD; i++) {
            printf("Leido desde memoria: Numero: %d, Letra: %c\n", memoria[i].numero, memoria[i].letra);
        }
        
        printSep();        
        libero_semaforo_spinner(id_semaforo, CUAL_SEMAFORO, TIEMPO_SLEEP);
    }

    logInfo("Liberando memoria");
    shmdt((char *)memoria);
    libero_memoria(id_memoria);
    logInfo("Programa terminado y memoria liberada");

    return 0;
}
