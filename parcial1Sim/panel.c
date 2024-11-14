#include "def.h"
#include "../shared/framework.h"

#define TIEMPO_SLEEP_PANEL 100

FILE* panelFile;
// store current message
panel pannel;

void leo(int panelId)
{
    panelFile = abrir_archivo_lectura(FILE_PATH);
    panel tempPanel;
    fseek(panelFile, panelId * sizeof(panel), SEEK_SET);
    fread(&tempPanel, sizeof(panel), 1, panelFile);
    // only print if panel message is different than stored one
    if (strcmp(tempPanel.mensaje, pannel.mensaje) != 0)
    {
        strcpy(pannel.mensaje, tempPanel.mensaje);
        printf("Panel %d: %s\n", tempPanel.nro_panel, tempPanel.mensaje);
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
    int id_semaforo = creo_semaforo(CANT_SEMAFORO);

    logInfof("Iniciando panel: %d", panelId);
    panelId--;

    while(1) 
    {
        espera_semaforo(id_semaforo, CUAL_SEMAFORO);
        leo(panelId);
        libero_semaforo(id_semaforo, CUAL_SEMAFORO);
        usleepMs(TIEMPO_SLEEP_PANEL);
    }
    
    return 0;
}