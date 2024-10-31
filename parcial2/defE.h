#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#define min_mosquito 3
#define max_mosquito 6
#define min_smoke 1
#define max_smoke 4

#define spinner_inicio 5

#define finish_line 95
#define turn_duration 300

#define amount_mosquitos 2
#define runners_amount 3

typedef enum {
MSG_MOSQUITO1,
MSG_MOSQUITO2,
MSG_SMOKE,
MSG_NONE,
MSG_POINTER,
} Destiny;

typedef enum {
EVT_NINGUNO, //0
EVT_CORRO, //1
EVT_FIN,
EVT_SOBREVIVIO,
} Eventos;


struct runner_config {
    int min_speed;
    int max_speed;
    Destiny runner;
};

typedef struct runnerStatus runnerStats;

struct runnerStatus
{
    int totalSteps;
    int alive;
    int finished;
    Destiny runner;
};

typedef struct sStatus sprintStatus;

struct sStatus
{
    int run;
};

#endif