#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "IOManager.h"
#include "HotPotato.h"

int main (int argc, char ** argv ) {

    srandom( time( 0 ) );
    std::cout << argc << std::endl;

    HotPotato hotPotato;
    IOManager output;    

    int players = 10;
    int potatoValue = 35;
    int rotationDirection = 1;

    if ( argc > 1 ) {
        players = atoi( argv[ 1 ] );
    }
    if ( argc > 2 ) {
        potatoValue = atoi( argv[ 2 ] );
    }
    if ( argc > 3 ) {
        rotationDirection = atoi( argv[ 3 ] );
    }

    int initialPlayer = (random() % players) * 10;

    int winner = hotPotato.Game(potatoValue, players, initialPlayer, rotationDirection);

    output.WinnerMsg(winner);

    return 0;

}