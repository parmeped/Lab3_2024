#include "../shared/framework.h"
#include "def.h"

int main()
{
    logInfo("Iniciando produccion");

    FILE *fp;
    int prod_id = 0;    
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
        
        for (prod_id ; i < lote_prod; prod_id++)
        {
            logInfo("Produciendo: %d", prod_id);
            fprintf(fp, "PRODUCTO-%02d\n", prod_id);
        }
        sleep(TIEMPO_SLEEP);
    }
    cerrar_archivo(fp);
    exit(0);
}