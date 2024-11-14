
#include "def.h"
#include "../../shared/framework.h"

FILE *equipoFile;

equipo equipos[MAX_TEAMS];

void fileSetup()
{
    equipoFile = abrir_archivo_escritura(FILE_PATH);
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        equipos[i].nro_equipo = i;
        equipos[i].puntos = 0;
        equipos[i].turno = 0;
        fwrite(&equipos[i], sizeof(equipo), 1, equipoFile);
    }
    cerrar_archivo(equipoFile);
}

int procesar_evento(int id_cola_mensajes, int semaphoreId, int turno, mensaje msg)
{
    // check for event
    switch (msg.int_evento)
    {
        case EVT_TURNO:
            logInfo("Recibido evento de turno");
            return turno;
        case EVT_TURNO_JUGADO:
                espera_semaforo(semaphoreId, CUAL_SEMAFORO);
                    logInfo("Recibido evento de turno jugado");
                    
                    // abro archivo
                    FILE* equiposFile = abrir_archivo_lectura(FILE_PATH);
                    
                    // muestro en pantalla turno, equipo, puntos y goles del que hizo el turno
                    fseek(equiposFile, msg.int_rte * sizeof(equipo), SEEK_SET);
                    fread(&equipos[msg.int_rte], sizeof(equipo), 1, equiposFile);
                    logInfof("Equipo %d, turno %d, puntos %d, goles %d", 
                        equipos[msg.int_rte].nro_equipo, equipos[msg.int_rte].turno, equipos[msg.int_rte].puntos, equipos[msg.int_rte].goles);
                    
                    // chequeo si todos jugaron el turno actual
                    for (int i = 0; i < MAX_TEAMS; i++)
                    {
                        if (equipos[i].turno < turno)
                        {
                            logInfo("No todos los equipos jugaron el turno actual");
                            libero_semaforo(semaphoreId, CUAL_SEMAFORO);
                            cerrar_archivo(equiposFile);
                            return turno;
                        }
                    }
                    
                    // si todos jugaron el turno actual, incremento el turno y retorno
                    turno++;

                    // cierro archivo
                    cerrar_archivo(equiposFile);
                libero_semaforo(semaphoreId, CUAL_SEMAFORO);
                return turno;
            break;
        case FIN:
            logInfo("Recibido evento de fin");
            break;
        default:
            logInfo("Evento sin definir");
            break;
    }
}

void enviarMensajeTurno(int id_cola_mensajes)
{
    logInfo("Empezando turnos");
    enviar_mensaje(id_cola_mensajes, MSG_EQUIPO1, MSG_PANEL, EVT_TURNO, "");
    enviar_mensaje(id_cola_mensajes, MSG_EQUIPO2, MSG_PANEL, EVT_TURNO, "");
}

int main(int argc, char *argv[])
{
    int maxGoals = atoi(argv[1]);
    if (maxGoals < 1) 
    {
        logInfo("Valor invalido para maximos goles");
        return 1;
    }
    // TODO: this is another win con!

	char cadena[LARGO_MENSAJE];
    int turno = 1;
	int id_cola_mensajes 	= creo_id_cola_mensajes(CLAVE_BASE);
    int id_semaforo = creo_semaforo(CANT_SEMAFORO);
    int ultTurno = 1;
	
    mensaje			msg;

    fileSetup();
    borrar_mensajes(id_cola_mensajes); //Borra todos los mensajes que haya en la cola.

    // envio mensaje de turno a todos los equipos
    enviarMensajeTurno(id_cola_mensajes);
    libero_semaforo(id_semaforo, CUAL_SEMAFORO);

	while(turno < MAX_TURNS + 1)
    {
        recibir_mensajes(id_cola_mensajes, MSG_PANEL, &msg);
		turno = procesar_evento(id_cola_mensajes, id_semaforo, turno, msg);
        if (turno != ultTurno)
        {
            ultTurno = turno;
            enviarMensajeTurno(id_cola_mensajes);
        }
        usleep(TIME_CHECK_MS);
	}
    
    logInfo("Finalizado");
    // envio evento fin a equipos
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        enviar_mensaje(id_cola_mensajes, i, MSG_PANEL, FIN, "");
    }

    // abro archivo, 
    FILE* equiposFile = abrir_archivo_lectura(FILE_PATH);
    // muestro en pantalla el equipo con mas puntos
    int maxPuntos = 0;
    int maxPuntosEquipo = 0;
    for (int i = 0; i < MAX_TEAMS; i++)
    {
        fseek(equiposFile, i * sizeof(equipo), SEEK_SET);
        fread(&equipos[i], sizeof(equipo), 1, equiposFile);
        if (equipos[i].puntos > maxPuntos)
        {
            maxPuntos = equipos[i].puntos;
            maxPuntosEquipo = i;
        }
    }

    logInfof("Equipo %d con %d puntos", maxPuntosEquipo, maxPuntos);
    // cierro archivo
    cerrar_archivo(equiposFile);

	return 0;
}