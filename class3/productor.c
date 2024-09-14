#include "../shared/framework.h"
#include "def.h"

int main()
{
    logInfo("Iniciando produccion");

    FILE *fp;
    int prod_id = 0;    
    int lote_prod = 10;
    while (1)
    {
        fp = append_archivo(DIR_ARCHIVO);
        if (fp == NULL)
        {
            logErr("No se puede abrir el archivo");
            exit(0);
        }
        
        for (int i = 0 ; i % lote_prod == 0; i++)
        {
            fprintf(fp, "PRODUCTO-%02d\n", i);
        }
        sleep(TIEMPO_SLEEP);
    }
    cerrar_archivo(fp);
    exit(0);
}