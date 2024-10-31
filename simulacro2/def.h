#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#define min_conejo 4
#define max_conejo 9
#define min_gato 1
#define max_gato 10
#define min_perro 3
#define max_perro 8

#define max_pasos 117

#define RUNNERS_AMOUNT 3

typedef enum {
MSG_NADIE, //0
MSG_TABLERO, //1
MSG_PERRO, // 2
MSG_GATO, // 3
MSG_CONEJO, // 4
} Destinos;

typedef enum {
EVT_NINGUNO, //0
EVT_CORRO, //1
EVT_FIN, //2
} Eventos;

struct animal_config {
    int min_speed;
    int max_speed;
    Destinos destino;    
};

typedef struct sprintAnimalStatus status;

struct sprintAnimalStatus
{
    int totalSteps;
    Destinos runner;
};

struct sprintStatus
{
    int run;
};

#endif