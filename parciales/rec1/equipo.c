#include "def.h"
#include "../../shared/framework.h"

equipo equipos[MAX_TEAMS];

int calcular_puntaje()
{
    return 10;
}

int procesar_evento_equipo(int messageQueueId, int teamId, int id_semaforo, mensaje msg)
{
    switch (msg.int_evento)
    {
        case EVT_TURNO:
            espera_semaforo(id_semaforo, CUAL_SEMAFORO);
                logInfo("Recibido evento de turno");
                // abro archivo lectura escritura
                FILE* equiposFile = abrir_archivo_escritura(FILE_PATH);

                // subo turno y calculo puntaje
                fseek(equiposFile, teamId * sizeof(equipo), SEEK_SET);
                fread(&equipos[teamId], sizeof(equipo), 1, equiposFile);
                equipos[teamId].turno++;
                equipos[teamId].puntos += calcular_puntaje();

                // guardo cambios
                fseek(equiposFile, teamId * sizeof(equipo), SEEK_SET);
                fwrite(&equipos[teamId], sizeof(equipo), 1, equiposFile);
                cerrar_archivo(equiposFile);
                enviar_mensaje(messageQueueId, MSG_PANEL, teamId, EVT_TURNO_JUGADO, "");
                logInfo("Jugado turno");
            libero_semaforo(id_semaforo, CUAL_SEMAFORO);
            return CONTINUE;
            break;
        case EVT_TURNO_JUGADO:
            logInfo("Recibido evento de turno jugado");
            return CONTINUE;
            break;
        case FIN:
            logInfo("Recibido evento de fin");
            return STOP;
            break;
        default:
            logInfo("Evento sin definir");
            return CONTINUE;
            break;
    }
    return CONTINUE;
}


int main(int argc, char *argv[])
{
    // check for teamId argument, try to parse to number
    int teamId = atoi(argv[1]);
    if (teamId < 1 || teamId > MAX_TEAMS) 
    {
        logInfo("Valor invalido de id para panel");
        return 1;
    }
    logInfof("Iniciando equipo: %d", teamId);
    teamId--;
    
    int id_semaforo = creo_semaforo(CANT_SEMAFORO);
    int id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
    int run = CONTINUE;
    mensaje			msg;

    libero_semaforo(id_semaforo, CUAL_SEMAFORO);

    //while(run) 
    while(1)
    {
        recibir_mensajes(id_cola_mensajes, teamId, &msg);

		run = procesar_evento_equipo(id_cola_mensajes, teamId, id_semaforo, msg);
        usleep(TIME_CHECK_MS);
    }
    logInfo("Exit");
    
    return 0;
}