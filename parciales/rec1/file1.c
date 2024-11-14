
#include "def.h"
#include "../../shared/framework.h"

#define LEO 1
#define ESCRIBO 2

FILE *panelFile;

panel paneles[MAX_PANNELS];

void fileSetup()
{
    panelFile = abrir_archivo_escritura(FILE_PATH);
    for (int i = 0; i < MAX_PANNELS; i++)
    {
        paneles[i].nro_panel = i;
        strcpy(paneles[i].mensaje, DEFAULT_MESSAGE);
        fwrite(&paneles[i], sizeof(panel), 1, panelFile);
    }
    cerrar_archivo(panelFile);
}

int panelNumberMenu() 
{
    int panelNumber;
    printf("Ingrese el numero de panel: ");
    while (scanf("%d", &panelNumber) != 1)
    {
        while (1)
        {
            printf("Numero de panel invalido, intente de nuevo: ");
            fflush(stdin);
            scanf("%d", &panelNumber);
            if (panelNumber >= 1 && panelNumber <= MAX_PANNELS)
            {
                break;
            }
        }
        fflush(stdin);
    }
    
    return panelNumber--;
}

void leo()
{
    int panelNumber = panelNumberMenu();
    
    logInfof("Panel seleccionado: %d", panelNumber);

    panelFile = abrir_archivo_lectura(FILE_PATH);

    fseek(panelFile, panelNumber * sizeof(panel), SEEK_SET);
    
    fread(&paneles[panelNumber], sizeof(panel), 1, panelFile);
    printf("Panel %d: %s\n", paneles[panelNumber].nro_panel, paneles[panelNumber].mensaje);
    cerrar_archivo(panelFile);
}

void escribo()
{
    int panelNumber = panelNumberMenu();
    
    logInfof("Panel seleccionado: %d", panelNumber);
    
    panelFile = abrir_archivo_escritura(FILE_PATH);    

    fseek(panelFile, panelNumber * sizeof(panel), SEEK_SET);

    paneles[panelNumber].nro_panel = panelNumber;
    printf("Ingrese el mensaje: ");
    scanf("%s", paneles[panelNumber].mensaje);
    fwrite(&paneles[panelNumber], sizeof(panel), 1, panelFile);
    cerrar_archivo(panelFile);
}

int menu(void)
{
    int opcion;

    printf("Menu\n\n");
    printf("1.\tLeer Panel\n");
    printf("2.\tEscribo mensaje\n");
    printf("0.\tSalir\n\n");
    printf("Elija opcion: ");
    fflush(stdin);  
    while( (scanf(" %d", &opcion) != 1)
          || (opcion < 0)            
          || (opcion > MAX_MENU))    
    {
      fflush(stdin);                 
      printf("No valido\n\n");
      printf("Elija opcion: ");
    }
    return opcion;
}

int main()
{
	char cadena[LARGO_MENSAJE];

	int id_semaforo, opcion;
	
	id_semaforo = creo_semaforo(CANT_SEMAFORO);
	inicio_semaforo(id_semaforo, CUAL_SEMAFORO, VERDE);
	
    fileSetup();

	opcion = menu();

	while(opcion != SALIR)
	{
		switch(opcion)
		{
			case LEO: 
                espera_semaforo(id_semaforo, CUAL_SEMAFORO);
                    leo();
                libero_semaforo(id_semaforo, CUAL_SEMAFORO);
                break;
			case ESCRIBO: 
                espera_semaforo(id_semaforo, CUAL_SEMAFORO);
                    escribo();
                libero_semaforo(id_semaforo, CUAL_SEMAFORO);
			    break;
			case SALIR: 
			    printf("Salir:\n");
			    break;
			default:    
			    printf("Opcion no valida\n");
		}

        usleepMs(TIEMPO_SLEEP);
		opcion = menu(); 
	}
	return 0;
}