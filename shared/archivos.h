#include "iarchivos.h"

FILE *abrir_archivo_lectura(char *path)
{
    return abrir_archivo(path, "r");
}

FILE *abrir_archivo_escritura(char *path)
{
    return abrir_archivo(path, "w");
}

FILE *append_archivo(char *path)
{
    return abrir_archivo(path, "a");
}

FILE *abrir_archivo(char *path, char *modo)
{
    logInfo("Abriendo archivo.");
    FILE *fp;
    fp = fopen(path, modo);

    if (fp == NULL)
    {
        logErr("No se encontró puntero para archivo.");
        exit(0);
    }
    return fp;
}

void cerrar_archivo(FILE *fp)
{
    logInfo("Cerrando archivo.");
    fclose(fp);
}

// Leer archivo completo
// append al archivo
