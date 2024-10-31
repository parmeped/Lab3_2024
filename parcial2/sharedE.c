#include "defE.h"
#include "../shared/framework.h"

const char* intToDestinoString(int destino) 
{
	switch (destino) 
	{
		case 0:
			return "Mosquito1";
		case 1:
			return "Mosquito2";
		case 2:
			return "Humo";
		default:
			return "Desconocido";
	}
}

const char* destinoToString(Destiny destino) 
{
    switch (destino) 
    {
        case MSG_MOSQUITO1:
            return "Mosquito1";
        case MSG_MOSQUITO2:
            return "Mosquito2";
        case MSG_SMOKE:
            return "Humo";
        default:
            return "Desconocido";
    }
}