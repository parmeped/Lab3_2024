#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H


#define LARGO_MENSAJE 100

#define STOP 0;
#define CONTINUE 1;

#define TIME_CHECK_MS 500

#define MAX_TEAMS 2
#define MAX_TURNS 6

#define FILE_PATH "equipos.dat"
#define DEFAULT_MESSAGE "default"

typedef enum
{
	MSG_EQUIPO1 = 0,
    MSG_EQUIPO2 = 1,
	MSG_PANEL = 2
}Destiny;

typedef enum
{
	EVY_NONE,
	EVT_TURNO, 
	EVT_TURNO_JUGADO,
	FIN
}Eventos;

typedef struct equipos equipo;

struct equipos
{
    int nro_equipo;
    int puntos;
    int turno;
    int goles;
};

#endif