#include "../../shared/framework.h"
#include "def.h"


int main(int caj_id)
{
    FILE *fp;
    int id_semaforo;
    char print_message[LARGO_MENSAJE];
    
    typedef struct {
        int importe_tot;
        int tipo_tot;
    } Transaccion;

    typedef struct {
        Transaccion transacciones[];
    }

    Transaccion transacciones[10]; // Array of 10 Transaccion objects

    sprintf(print_message, "Comenzando cajero con Id: %s", caj_id);
    logInfo(print_message);
    
    id_semaforo = creo_semaforo(SEM_AMOUNT);
    inicio_semaforo(id_semaforo, SEM_NUMBER, SEM_VERDE);

    while(1) 
    {
        espera_semaforo(id_semaforo, SEM_NUMBER);



        libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, TESORERO_SLEEP_MS);
    }
}