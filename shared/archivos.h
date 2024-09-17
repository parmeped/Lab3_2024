#include "iarchivos.h"
#include "icommon.h"

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
    char msg[100];
    sprintf(msg, "Abriendo archivo: %s, modo: %s", path, modo);
    
    logWarn(msg);
    FILE *fp;
    fp = fopen(path, modo);

    if (fp == NULL)
    {
        logErr("No se encontro puntero para archivo.");
        return NULL;
    }
    return fp;
}

void cerrar_archivo(FILE *fp)
{    
    logWarn("Cerrando archivo.");
    fclose(fp);
}

void borrar_archivo(char *path)
{
    char msg[100];
    sprintf(msg, "Borrando archivo: %s", path);

    logWarn(msg);
    remove(path);
}

int renombrar_archivo(char *viejo_nombre, char *nuevo_nombre)
{
    return rename(viejo_nombre, nuevo_nombre);
}

// Leer archivo completo
// append al archivo
