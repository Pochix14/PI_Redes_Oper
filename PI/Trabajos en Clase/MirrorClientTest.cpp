
/**
 *   UCR-ECCI
 *   CI-0123 Proyecto integrador de redes y sistemas operativos
 *
 *   Socket client/server example
 *
 **/

#include <stdio.h>
#include "Socket.h"

#define PORT 5678
#define BUFSIZE 512

int main( int argc, char ** argv ) {
   Socket s('s');     // Crea un socket de IPv4, tipo "stream"
   char buffer[ BUFSIZE ];

    //For IPv4
   s.Connect( "10.1.35.6", PORT ); // Same port as server
   //For IPv6
   //char * os = (char*)"fe80::2444:6589:d1c4:f8ce%eno1";
   //s.Connect(os, (char*)"https");
   if ( argc > 1 ) {
      s.Write( argv[1] );		// Send first program argument to server
   } else {
      s.Write( "Hello world 2023 ..." );
   }
   s.Read( buffer, BUFSIZE );	// Read answer sent back from server
   printf( "%s", buffer );	// Print received string

}