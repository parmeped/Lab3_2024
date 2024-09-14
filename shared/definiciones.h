#ifndef _DEFINICIONES_H
#define _DEFINICIONES_H

#define LARGO_DESCRIPCION 100
#define CANT_SEMAFORO 1

#define LARGO_MENSAJE 1024

#define SEM_VERDE 1
#define SEM_ROJO 0

typedef struct tipo_datos datos;
struct tipo_datos
{
    int dato;
};

typedef enum 
{
    MSG_NADIE,
    MSG_SUPERMERCADO,
    MSG_REPOSITOR
}Destinos;

typedef enum 
{
    EVT_NINGUNO,
    EVT_CONSULTA_STK,
    EVT_RESPUESTA_STK,
    EVT_SUMA_STK,
    EVT_RESTA_STK
}Eventos;

#endif
