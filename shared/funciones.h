#include "ifunciones.h"
#include "icommon.h"

key_t creo_clave(int r_clave)
{
    key_t clave;
    clave = ftok("/bin/ls", r_clave);

    if (clave == (key_t)-1)
    {
        printf("Error: no se puede conseguir clave para memoria compartida\n");
        exit(0);
    }
    return clave;
}

void *creo_memoria(int size, int *r_id_memoria, int clave_base)
{
    void *ptr_memoria;
    int id_memoria;
    id_memoria = shmget(creo_clave(clave_base), size, 0777 | IPC_CREAT);

    if (id_memoria == -1)
    {
        printf("Error: no se puede conseguir memoria compartida\n");
        exit(0);
    }

    ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);
    if (ptr_memoria == NULL)
    {
        printf("Error: no se puede conseguir memoria compartida\n");
        exit(0);
    }
    *r_id_memoria = id_memoria;
    return ptr_memoria;
}

int creo_semaforo(int cantidad)
{
    key_t clave = creo_clave(CLAVE_BASE);
    int id_semaforo = semget(clave, cantidad, 0600 | IPC_CREAT);
    if (id_semaforo == -1)
    {
        printf("Error: no se puede crear semaforo \n");
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
        printf("Error: no se pudo crear identificador para cola mensajes\n");
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
    strcpy(msg.char_mensaje, message);
    return msgsnd(id_cola, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), IPC_NOWAIT);
}

int recibir_mensajes(int id_cola, long dest, mensaje *message)
{
    mensaje msg;
    int res;
    res = msgrcv(id_cola, (struct msgbuf *)&msg, sizeof(msg.int_rte) + sizeof(msg.int_evento) + sizeof(msg.char_mensaje), dest, 0);

    message->long_dest = msg.long_dest;
    message->int_rte = msg.int_rte;
    message->int_evento = msg.int_evento;
    strcpy(message->char_mensaje, msg.char_mensaje);

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
