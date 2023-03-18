#ifndef Sem_h
#define Sem_h

/**
 * Librerias: Semget, semctl, semop
 * Para ver los semaforos: ipcs
 * 
*/

/*
 * Para crear areas de memoria compatida
 * Libreria: shmget (el key es el del sem)
 * Libreria: shmat  (para hacer el atach de los sem)
 * El shmat retorna un void*, que debe ser casteado a lo que se necesite
 * Libreria: shmctl para destruir el area de memoria
*/



class Sem {
    public:
        //Se hace con semget, se inicializa con semctl
        Sem(int = 0);
        //Se hace con semctl 
        ~Sem();
        //Se hacen con semop
        int Wait();
        int Signal();

    private:
        int idSem;
};

#endif