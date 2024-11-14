#include "def.h"
#include "../shared/framework.h"

#define TIEMPO_SLEEP_PANEL 100

FILE* panelFile;
// store current message
panel pannel;

void leo(int *panelId)
{
    panelFile = abrir_archivo_lectura(FILE_PATH);
    fseek(panelFile, *panelId * sizeof(panel), SEEK_SET);
    fread(&paneles[*panelId], sizeof(panel), 1, panelFile);
    // only print if panel message is different than stored one
    if (strcmp(paneles[*panelId].mensaje, pannel.mensaje) != 0)
    {
        strcpy(pannel.mensaje, paneles[*panelId].mensaje);
        printf("Panel %d: %s\n", paneles[*panelId].nro_panel, paneles[*panelId].mensaje);
    }
    cerrar_archivo(panelFile);
}

// receive panel id through args
int main(int argc, char *argv[])
{
    
    // check for panelId argument, try to parse to number
    int panelId = atoi(argv[1]);
    if (panelId < 1) 
    {
        logInfo("Valor invalido de id para panel");
        return 1;
    }
    panelId--;
    int id_semaforo = creo_semaforo(CANT_SEMAFORO);

    while(1) 
    {
        espera_semaforo(id_semaforo, CUAL_SEMAFORO);
        leo(panelId);
        libero_semaforo(id_semaforo, CUAL_SEMAFORO);
        usleepMs(TIEMPO_SLEEP_PANEL);
    }
    
    return 0;
}