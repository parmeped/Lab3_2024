#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/sem.h>

#define CANTIDAD_PARTIDA 	10
#define INTERVALO_PRODUCTO 	100
#define INTERVALO_PARTIDA 	5000
#define ROJO  			0
#define VERDE 			1
#define LARGO 			100


key_t creo_clave()
{
	// Igual que en cualquier recurso compartido (memoria compartida, semaforos
	// o colas) se obtien una clave a partir de un fichero existente cualquiera
	// y de un entero cualquiera. Todos los procesos que quieran compartir este
	// semaforo, deben usar el mismo fichero y el mismo entero.
	key_t clave;
	clave = ftok ("/bin/ls", 33);
	if (clave == (key_t)-1)
	{
		printf("No puedo conseguir clave de sem�foro\n");
		exit(0);
	}
	return clave;
}


//funcion que crea el semaforo
int creo_semaforo()
{
	key_t clave = creo_clave();
	int id_semaforo = semget(clave, 1, 0600|IPC_CREAT); 
	//PRIMER PARAMETRO ES LA CLAVE, EL SEGUNDO CANT SEMAFORO, EL TERCERO 0600 LO UTILIZA CUALQUIERA, IPC ES CONSTANTE (VEA SEMAFORO)
	if(id_semaforo == -1)
	{
	printf("Error: no puedo crear semaforo\n");
	exit(0);
	}
	return id_semaforo;
}

//inicia el semaforo
void inicia_semaforo(int id_semaforo, int valor)
{
	semctl(id_semaforo, 0, SETVAL, valor);
}

//levanta el semaforo
void levanta_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Levanta SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = 1; //incrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);
}

//espera semaforo
void espera_semaforo(int id_semaforo)
{
	struct sembuf operacion;
	printf("Espera SEMAFORO \n");
	operacion.sem_num = 0;
	operacion.sem_op = -1; //decrementa el semaforo en 1
	operacion.sem_flg = 0;
	semop(id_semaforo,&operacion,1);

}

int main()
{
	char cadena[LARGO]; /* Un array lo suficientemente grande como para guardar la l�nea m�s larga del fichero */
	int nro_producto=0, nro_partida=0;
	FILE *productor; 

	
	int id_semaforo;
	
	id_semaforo =  creo_semaforo();
	inicia_semaforo(id_semaforo, VERDE);
	
	while(1)
	{
		espera_semaforo(id_semaforo);
			
			printf("\nPRODUCIMOS-PARTIDA-%04d\n",nro_partida);
			productor = fopen("producto.txt", "a");
			if (productor!=NULL)
			{
				for (nro_producto=0; nro_producto<CANTIDAD_PARTIDA; nro_producto++)
				{
					sprintf(cadena, "PRODUCTO-%04d-%04d\n", nro_partida, nro_producto);
					printf("%s", cadena);
					fprintf(productor,"%s",cadena);
					usleep(INTERVALO_PRODUCTO*1000);
				}
				fclose(productor);
				nro_partida++;
				printf("\nESPERAMOS\n");
			}
			else
			{
				perror ("Error al abrir producto.txt");
			}
			
		levanta_semaforo(id_semaforo);
		usleep(INTERVALO_PARTIDA*1000);
	};
	return 0;
}
