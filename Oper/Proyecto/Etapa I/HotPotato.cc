#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "HotPotato.h"
#include "ShrMemory.h"

HotPotato::HotPotato() {
    this->id = -1;
    this->active = true;
}

HotPotato::~HotPotato() {

}

int HotPotato::Game(int potatoInitialValue, int players, int initialPlayer, int rotation) {
    int winner = 0;

    ShrMemory segment( 1024 );
    sem_t sem;
    sem_init( &sem, 1, 1);

    pid_t main = getpid();
    for (int i = 1; i < players; ++i) {
        if (getpid() == main) {
            fork();
            id = 10 * i;
            active = true;
            if (getpid() != main && i == players -1) {
                id += 10;
            }
        } else {
            break;
        }
    }

    sharedMemory = (msgbuf *) segment.attach();

    if (id == initialPlayer) {
        sharedMemory->currentPlayer = initialPlayer;
        sharedMemory->potatoValue = potatoInitialValue;
        sharedMemory->players = players;
        sharedMemory->remainPlayers = players;
        sharedMemory->nextPlayer = initialPlayer + (rotation * 10);
        sharedMemory->rotationDirection = rotation;
        sharedMemory->gameOver = false;
    }
    

    while(!sharedMemory->gameOver) {
        sem_wait(&sem);
        if (!sharedMemory->gameOver) {
        if (sharedMemory->remainPlayers == 1 && active) {
            sharedMemory->gameOver = true;
            winner = id;
        } else {
            if (sharedMemory->currentPlayer == id) {
                if (active) {
                    output.CurrentPlayer(id);
                    int potatoValue = Collatz(sharedMemory->potatoValue);
                    output.PotatoValue(potatoValue);
                    if (potatoValue == 1) {
                        active = false;
                        --sharedMemory->remainPlayers;
                        sharedMemory->potatoValue = PotatoNewValue();
                        output.PotatoExplote(id);
                    } else {
                        sharedMemory->potatoValue = potatoValue;
                    }
                }
                if (sharedMemory->rotationDirection == 1) { //To right
                    if (sharedMemory->nextPlayer > (sharedMemory->players * 10)) {
                        sharedMemory->currentPlayer = 10;
                        sharedMemory->nextPlayer = sharedMemory->currentPlayer + 10;
                    } else {
                        sharedMemory->currentPlayer = sharedMemory->nextPlayer;
                        sharedMemory->nextPlayer = sharedMemory->currentPlayer + 10;
                    }
                } else { // To left
                    if (sharedMemory->nextPlayer < 10) {
                        sharedMemory->currentPlayer = sharedMemory->players * 10;
                        sharedMemory->nextPlayer = sharedMemory->currentPlayer - 10;
                    } else {
                        sharedMemory->currentPlayer = sharedMemory->nextPlayer;
                        sharedMemory->nextPlayer = sharedMemory->currentPlayer - 10;
                    }
                }
            }
        }
        }
        sem_post(&sem);
    }

    segment.detach();

    return winner;
}

int HotPotato::Collatz (int potatoValue) {
    // Odd
    if ( 1 == (potatoValue & 0x1) ) {
        // (Potato * 2) + potato + 1
        potatoValue = (potatoValue << 1) + potatoValue + 1;
    } else {
        // Potato / 2
        potatoValue >>= 1;
    }
   return potatoValue;
}

int HotPotato::PotatoNewValue() {
    return random() % 40;
}