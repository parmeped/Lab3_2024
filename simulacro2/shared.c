#include "def.h"
#include "../shared/framework.h"

const int destinoToInt(Destinos destino) 
{
    switch (destino) 
    {
        case MSG_PERRO:
            return 0;
        case MSG_GATO:
            return 1;
        case MSG_CONEJO:
            return 2;
        default:
            return -1;
    }
}

const char* intToDestino(int destino) 
{
	switch (destino) 
	{
		case 0:
			return "Perro";
		case 1:
			return "Gato";
		case 2:
			return "Conejo";
		default:
			return "Desconocido";
	}
}

const char* destinoToString(Destinos destino) 
{
    switch (destino) 
    {
        case MSG_PERRO:
            return "Perro";
        case MSG_GATO:
            return "Gato";
        case MSG_CONEJO:
            return "Conejo";
        default:
            return "Desconocido";
    }
}