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
    while (1)
    {
        lote_prod = prod_quota + prod_id;
        fp = append_archivo(DIR_ARCHIVO);
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
        sprintf(info, "Durmiendo por %d", TIEMPO_SLEEP);
        logWarn(info);
        sleep(TIEMPO_SLEEP);
    }
    exit(0);
}