#include "../../shared/framework.h"
#include "def.h"

int main(int caj_id)
{
    FILE *fp;
    int id_semaforo;
    char print_message[LARGO_MENSAJE];
    char nombre_archivo[100];
    int importe;
    int tipo;
    int tiempo_espera;

    sprintf(print_message, "Comenzando cajero con Id: %d", caj_id);
    logInfo(print_message);
    
    sprintf(nombre_archivo, NOMBRE_ARCHIVO_CAJ, caj_id);

    id_semaforo = creo_semaforo(SEM_AMOUNT);
    inicio_semaforo(id_semaforo, 0, SEM_VERDE);

    while(1) 
    {
        espera_semaforo(id_semaforo, SEM_NUMBER);
        fp = abrir_archivo_lectura(nombre_archivo);
        if (fp == NULL) 
        {
            fp = abrir_archivo_escritura(nombre_archivo);
        }
        else 
        {
            cerrar_archivo(fp);
            fp = append_archivo(nombre_archivo);
        }

        logInfo("Cargando depositos...");
        for(int i = 0; i < randomNumber(MIN_LOTE_CAJERO, MAX_LOTE_CAJERO); i++) 
        {
            importe = randomNumber(MIN_IMPORTE_CAJERO, MAX_IMPORTE_CAJERO);
            tipo = randomNumber(VAL_CHEQUE, VAL_EFECTIVO);
            fprintf(fp, STRING_FILE, importe, tipo);
        }
        fclose(fp);
        tiempo_espera = randomNumber(CAJERO_MIN_SLEEP_MS, CAJERO_MAX_SLEEP_MS);
        libero_semaforo_mspinner(id_semaforo, SEM_NUMBER, tiempo_espera);
        break;
    }
    exit(0);
}