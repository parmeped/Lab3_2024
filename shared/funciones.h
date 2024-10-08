#include "ifunciones.h"
#include "icommon.h"

key_t creo_clave(int r_clave)
{
    key_t clave;
    clave = ftok("/bin/ls", r_clave);

    if (clave == (key_t)-1)
    {
        logErr("No se puede conseguir clave para memoria compartida");
        exit(0);
    }
    return clave;
}

int creo_semaforo(int cantidad)
{
    key_t clave = creo_clave(CLAVE_BASE);
    int id_semaforo = semget(clave, cantidad, 0600 | IPC_CREAT);
    if (id_semaforo == -1)
    {
        logErr("No se puede crear semaforo.");
        exit(0);
    }
    return id_semaforo;
}

void inicio_semaforo(int id, int cual, int valor)
{
    semctl(id, cual, SETVAL, valor);
}

void sem_oper(int id, int cual, int op)
{
    struct sembuf operacion;
    operacion.sem_num = cual;
    operacion.sem_op = op;
    operacion.sem_flg = 0;
    semop(id, &operacion, 1);
}

void libero_semaforo(int id, int cual)
{
    sem_oper(id, cual, 1);
    usleep(100);
}

void libero_semaforo_spinner(int id, int cual, int sleepTime)
{
    sem_oper(id, cual, 1);
    spinner(sleepTime);
}

void libero_semaforo_mspinner(int id, int cual, int sleepTime)
{
    sem_oper(id, cual, 1);
    mSpinner(sleepTime);
}

void espera_semaforo(int id, int cual)
{
    sem_oper(id, cual, -1);
}

int creo_id_cola_mensajes(int clave)
{
    int id_cola = msgget(creo_clave(clave), 0600 | IPC_CREAT);
    if (id_cola == -1)
    {
        logErr("No se pudo crear identificador para cola mensajes.");
        exit(0);
    }
    return id_cola;
}

int enviar_mensaje(int id_cola, long dest, int rte, int evento, char *message)
{
    mensaje msg;
    msg.long_dest = dest;
    msg.int_rte = rte;
    msg.int_evento = evento;
    strncpy(msg.char_mensaje, message, sizeof(msg.char_mensaje) - 1);
    msg.char_mensaje[sizeof(msg.char_mensaje) - 1] = '\0';
    return msgsnd(id_cola, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), IPC_NOWAIT);
}

int recibir_mensajes(int id_cola, long dest, mensaje *message)
{
    mensaje msg;
    int res;
    res = msgrcv(id_cola, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), dest, 0);

    if (res != -1)
    {
        message->long_dest = msg.long_dest;
        message->int_rte = msg.int_rte;
        message->int_evento = msg.int_evento;
        strncpy(message->char_mensaje, msg.char_mensaje, sizeof(message->char_mensaje) - 1);
        message->char_mensaje[sizeof(message->char_mensaje) - 1] = '\0';
    }

    return res;
}

int borrar_mensajes(int id_cola)
{
    mensaje msg;
    int res;
    do
    {
        res = msgrcv(id_cola, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), 0, IPC_NOWAIT);
    } while (res > 0);
    return res;
}

int randomNumber(int min, int max)
{
    srand(time(NULL));
    return (rand() % (max - min + 1)) + min;
}

int randomNumberPrevSeed(int min, int max, int prevRandSeed)
{
    srand(time(NULL) + prevRandSeed);
    return (rand() % (max - min + 1)) + min;
}

void substring(const char *string, int position, int length, char *result)
{
    int c;
    for (c = 0; c < length && string[position + c] != '\0'; c++)
    {
        result[c] = string[position + c];
    }
    result[c] = '\0';
}
