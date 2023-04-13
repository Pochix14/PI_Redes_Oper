#ifndef HotPotato_h
#define HotPotato_h

#include "IOManager.h"

class HotPotato {
    public:
        HotPotato();
        ~HotPotato();
        int Game (int, int, int, int);
        int Collatz(int);
        int PotatoNewValue();

    private:
        struct msgbuf {			
            long currentPlayer;
            int potatoValue;
            int players;
            int remainPlayers;
            int nextPlayer;
            int rotationDirection;
            bool gameOver;
        } *sharedMemory;

        int id;
        bool active;

        IOManager output;
};

#endif