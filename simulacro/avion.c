#include "../shared/archivos.h"
#include "../shared/definiciones.h"
// ingreso de ciudad por teclado, ingreso de nro avion por param

#define archivo_aviones "aviones.dat"

int main(int nro_avion) 
{
    char ciudad[15];
    char info[100];

    logInfo("Favor de ingresar ciudad de pertenencia");
    scanf("%s", ciudad);
    sprintf(info, "Avion nro: %d, ciudad pertenencia: %s\n", nro_avion, ciudad);
    logInfo(info);
    
    FILE *fp = append_archivo(archivo_aviones);
    if (fp == NULL) 
    {
        logErr("Cerrando programa por error en archivo");
        exit(0);
    }
    fprintf(fp, "ciudad: %s, nro_avion: %d", ciudad, nro_avion);
    cerrar_archivo(fp);

    exit(0);
}