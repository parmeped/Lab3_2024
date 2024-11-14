#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H


#define LARGO_MENSAJE 100

#define MAX_PANNELS 3
#define MAX_MENU 2

#define FILE_PATH "paneles.dat"
#define DEFAULT_MESSAGE "default"

typedef struct paneles panel;

struct paneles
{
    int nro_panel;
    char mensaje[LARGO_MENSAJE];
};

#endif