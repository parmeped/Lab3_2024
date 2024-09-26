#include "icommon.h"

void *creo_memoria(int size, int *r_id_memoria, int clave_base)
{
    void *ptr_memoria;
    int id_memoria;
    id_memoria = shmget(creo_clave(clave_base), size, 0777 | IPC_CREAT);

    if (id_memoria == -1)
    {
        logErr("No se puede conseguir memoria compartida.");
        exit(0);
    }

    ptr_memoria = (void *)shmat(id_memoria, (char *)0, 0);
    if (ptr_memoria == (void *)-1)
    {
        logErr("No se puede conseguir memoria compartida.");
        exit(0);
    }
    *r_id_memoria = id_memoria;
    return ptr_memoria;
}

void libero_memoria(int id)
{
    shmctl(id, IPC_RMID, (struct shmid_ds *)NULL);
}