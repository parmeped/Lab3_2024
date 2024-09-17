#include "../shared/framework.h"
#include "def.h"

int main()
{
    logInfo("Iniciando produccion");

    FILE *fp;
    char info[100];

    int prod_id = 1;    
    int lote_prod = 10;    
    int prod_quota = 10;
    int read_prod_id;
    int mini_sleep = TIEMPO_SLEEP_CARGA / 10;
    while (1)
    {
        lote_prod = prod_quota + prod_id;
        fp = abrir_archivo_escritura(DIR_ARCHIVO);
        if (fp == NULL)
        {
            logErr("No se puede abrir el archivo");
            exit(0);
        }
        
        for (; prod_id < lote_prod; prod_id++)
        {
            sprintf(info, "Produciendo: %d", prod_id);
            logInfo(info);
            fprintf(fp, "PRODUCTO-%02d\n", prod_id);
        }

        cerrar_archivo(fp);
        sprintf(info, "Durmiendo por %d", mini_sleep);
        logWarn(info);
        sleep(mini_sleep);

        logInfo("Consumiendo productos");

        fp = abrir_archivo_lectura(DIR_ARCHIVO);
        if (fp == NULL)
        {
            logErr("No se puede abrir el archivo");
            exit(0);
        }

        while (!feof(fp))
        {
            fscanf(fp, "PRODUCTO-%02d\n", &read_prod_id);
            sprintf(info, "Consumido producto: %d", read_prod_id);
            logInfo(info);
        }
        cerrar_archivo(fp);

        sprintf(info, "Durmiendo por %d", TIEMPO_SLEEP_CARGA);
        logWarn(info);
        sleep(TIEMPO_SLEEP_CARGA);       
    }
    exit(0);
}