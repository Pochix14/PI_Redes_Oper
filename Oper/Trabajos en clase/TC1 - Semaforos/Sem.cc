#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#include "Sem.h"

//Union para definir valor inicial del semaforo
union semun {
    int val; // Valor de setval
    struct semid_ds *buf; // Buffer para IPC_STAT, IPC_SET
    unsigned short *array; // Arreglo para getall, setall
    struct seminfo *__buf; //Buffer para IPC_INFO
};

/**
 * Constructor
 * Crear un arreglo de semaforos
 * @param valorInicial valor inicial de los semaforos del arreglo
*/
Sem::Sem(int valorInicial) {
    union semun x;
    int status = semget(0xB66060, 1, IPC_CREAT | 0600);
    if (status == -1) {
        perror("Error al crear arreglo de semaforos");
        exit(2);
    }
    this->idSem = status;
    x.val = 0;

    status = semctl(this->idSem, 0, SETVAL, x);
    if (status == -1) {
        perror("Error al inicializar el valor del semaforo");
        exit(2);
    }
}

Sem::~Sem() {
    int status = semctl(this->idSem, 0, IPC_RMID);
    if (status == -1) {
        perror("Error al eliminar el semaforo");
        exit(2);
    }
}

int Sem::Wait() {
    int status = -1;
    struct sembuf z;
    z.sem_num = 0;
    z.sem_op = -1;
    z.sem_flg = 0;

    status = semop(this->idSem, &z, 1);
    if (status == -1) {
        perror("Error al hacer wait al semaforo");
        exit(2);
    }   

    return status;
}

int Sem::Signal() {
    int status = -1;
    struct sembuf z;
    z.sem_num = 0;
    z.sem_op = 1;
    z.sem_flg = 0;

    status = semop(this->idSem, &z, 1);
    if (status == -1) {
        perror("Error al hacer signal al semaforo");
        exit(2);
    }   

    return status;
}

int main (int argc, char ** args) {
    Sem s(0);
    if (fork()) {
        s.Wait();
        printf("Si\n");
    } else {
        printf("No\n");
        s.Signal();
    }
}