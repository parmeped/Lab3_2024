#include "../../shared/framework.h"
#include "def.h"


int main(int caj_id)
{
    FILE *fp;
    int id_semaforo;
    char print_message[LARGO_MENSAJE];

    sprintf(print_message, "Comenzando cajero con Id: %s", caj_id);
    logInfo(print_message);
    
    id_semaforo = creo_semaforo(1);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    while(1) 
    {
        espera_semaforo(id_semaforo, 0);
        libero_semaforo_mspinner(id_semaforo, 0, TESORERO_SLEEP_MS);
    }
}