#include "../shared/framework.h"
#include "def.h"

#include <signal.h>

volatile sig_atomic_t stop;

void handle_sigint(int sig) {
    stop = 1;
}

int main() {
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
        for (i = 0; i < CANTIDAD; i++) {
            aleatorio = rand() % 100;
            memoria[i].numero = aleatorio;
            memoria[i].letra = 'A' + (aleatorio % 26);
            printf("Escrito en memoria: Numero: %d, Letra: %c\n", memoria[i].numero, memoria[i].letra);
        }
        
        logInfo("Memoria escrita");
        libero_semaforo_spinner(id_semaforo, CUAL_SEMAFORO, 1);
    }

    logInfo("Liberando memoria");
    shmdt((char *)memoria);
    shmctl(id_memoria, IPC_RMID, (struct shmid_ds *)NULL);
    logInfo("Programa terminado y memoria liberada");

    return 0;
}
