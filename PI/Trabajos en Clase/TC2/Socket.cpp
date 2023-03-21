/**
 *   CI0123 PIRO
 *   Clase para utilizar los "sockets" en Linux
 *
 **/

#include <stdio.h>	// for perror
#include <stdlib.h>	// for exit
#include <string.h>	// for memset
#include <arpa/inet.h>	// for inet_pton
#include <sys/types.h>	// for connect 
#include <sys/socket.h>
#include <unistd.h> // for close
#include <netdb.h> // for struct addrinfo IPv6

#include "Socket.h"

/**
  *  Class constructor
  *     use Unix socket system call
  *
  *  @param	char type: socket type to define
  *     's' for stream
  *     'd' for datagram
  *  @param	bool ipv6: if we need a IPv6 socket
  *
 **/
Socket::Socket( char type, bool IPv6 ){
    if (type == 's') {
      if (IPv6) {
         idSocket = socket(AF_INET6, SOCK_STREAM, 0);
      } else {
         idSocket = socket(AF_INET, SOCK_STREAM, 0);
      }
    } else {
        if (IPv6) {
            idSocket = socket(AF_INET6, SOCK_DGRAM, 0);
        } else {
            idSocket = socket(AF_INET, SOCK_STREAM, 0);
        }
    }
}


/**
  * Class destructor
  *
 **/
Socket::~Socket(){
    Close();
}


/**
  * Close method
  *    use Unix close system call (once opened a socket is managed like a file in Unix)
  *
 **/
void Socket::Close(){
    close(idSocket);
}

/**
  * Connect method
  *   use "connect" Unix system call
  *
  * @param	char * host: host address in dot notation, example "10.1.104.187"
  * @param	int port: process address, example 80
  *
 **/
int Socket::Connect( const char * host, int port ) {
   int st;
   if (!this->ipv6) {
      struct sockaddr_in  host4;
      struct sockaddr * ha;

      memset( (char *) &host4, 0, sizeof( host4 ) );
      host4.sin_family = AF_INET;
      inet_pton( AF_INET, host, &host4.sin_addr );
      host4.sin_port = htons( port );
      ha = (sockaddr*)&host4;
      st = connect( idSocket, (sockaddr *) ha, sizeof( host4 ) );
      if ( -1 == st ) {	// check for errors
         perror( "Socket::Connect" );
         exit( 2 );
      }
   } else {
      //No es necesario, no sirve para IPv6
      struct sockaddr_in6  host6;
      struct sockaddr * ha;

      memset( &host6, 0, sizeof( host6 ) );
      host6.sin6_family = AF_INET6;
      st = inet_pton( AF_INET6, host, &host6.sin6_addr );
      if ( 1 == st ) {	// 0 means invalid address, -1 means address error
         perror( "Socket::Connect, inet_pton" );
         exit( 2 );
      }
      host6.sin6_port = htons( port );
      ha = (struct sockaddr *) &host6;
      long len = sizeof( host6 );
      st = connect( this->idSocket, ha, len );
      if ( -1 == st ) {
         perror( "Socket::Connect, connect" );
         exit( 2 );
      }
   }

   return st;

}


/**
  * Connect method
  *
  * @param	char * host: host address in dot notation, example "163.178.104.187"
  * @param	char * service: service name, example "http"
  *
 **/
int Socket::Connect( const char *host, const char *service ) {
   int st = -1;

   struct addrinfo hints, *result, *rp;

   memset(&hints, 0, sizeof(struct addrinfo));
   hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
   hints.ai_socktype = SOCK_STREAM; /* Stream socket */
   hints.ai_flags = 0;
   hints.ai_protocol = 0;          /* Any protocol */

   st = getaddrinfo( host, service, &hints, &result );

   for ( rp = result; rp; rp = rp->ai_next ) {
      st = connect( idSocket, rp->ai_addr, rp->ai_addrlen );
      if ( 0 == st )
         break;
   }

   freeaddrinfo( result );


   return st;

}


/**
  * Read method
  *   use "read" Unix system call (man 3 read)
  *
  * @param	void * text: buffer to store data read from socket
  * @param	int size: buffer capacity, read will stop if buffer is full
  *
 **/
int Socket::Read( void * text, size_t size ) {
   int st = -1;

   st = read(idSocket, text, size);

   return st;

}


/**
  * Write method
  *   use "write" Unix system call (man 3 write)
  *
  * @param	void * buffer: buffer to store data write to socket
  * @param	size_t size: buffer capacity, number of bytes to write
  *
 **/
int Socket::Write( const void *text, size_t size ) {
   int st = -1;

    st = write(idSocket, text, size);

   return st;

}


/**
  * Write method
  *
  * @param	char * text: string to store data write to socket
  *
  *  This method write a string to socket, use strlen to determine how many bytes
  *
 **/
int Socket::Write( const char *text ) {
   int st = -1;

   st = write(idSocket, text, strlen(text));

   return st;

}


/**
  * Listen method
  *   use "listen" Unix system call (server mode)
  *
  * @param	int queue: max pending connections to enqueue 
  *
  *  This method define how many elements can wait in queue
  *
 **/
int Socket::Listen( int queue ) {
    int st = -1;

    st = listen(this->idSocket, queue);

    if (st == -1) {
        perror("Error en listen");
        exit(2);
    }

    return st;

}


/**
  * Bind method
  *    use "bind" Unix system call (man 3 bind) (server mode)
  *
  * @param	int port: bind a socket to a port defined in sockaddr structure
  *
  *  Links the calling process to a service at port
  *
 **/
int Socket::Bind( int port ) {
   int st = -1;
   struct sockaddr * ha;
   struct sockaddr_in host4;
   struct sockaddr_in6 host6;

   //memset(&host4, 0, sizeof(host4));
   host4.sin_family = AF_INET;
   host4.sin_port = htons(port);
   host4.sin_addr.s_addr = INADDR_ANY;

   st = bind(this->idSocket, (struct sockaddr*) &host4, sizeof(struct sockaddr_in));
      
   /*if (st == -1) {
      perror("Error en bind");
      exit(2);
   }*/

   return st;

}


/**
  * Accept method
  *    use "accept" Unix system call (man 3 accept) (server mode)
  *
  *  @returns	a new class instance
  *
  *  Waits for a new connection to service (TCP  mode: stream)
  *
 **/
Socket * Socket::Accept(){

   return (Socket *) 0;

}


/**
  * Shutdown method
  *    use "shutdown" Unix system call (man 3 shutdown)
  *
  *  @param	int mode define how to cease socket operation
  *
  *  Partial close the connection (TCP mode)
  *
 **/
int Socket::Shutdown( int mode ) {
   int st = -1;

   return st;

}


/**
  *  SetIDSocket
  *
  *  @param	int id assigns a new value to field
  *  
 **/
void Socket::SetIDSocket(int id){

    this->idSocket = id;

}

int Socket::sendTo(const void *buf, size_t len, const void *sockaddrs) {
   int st = -1;

   st = sendto(this->idSocket, buf, len, 0, (struct sockaddr *) sockaddrs, 
               sizeof(struct sockaddr_in));

   /*if (st == -1) {
      perror("Error al enviar mensaje\n");
      exit(2);
   }*/

   return st;
}

int Socket::recvFrom( void *buf, size_t len, const void *sockaddrs) {
   int st = -1;

   int size = sizeof(struct sockaddr_in);

   st = recvfrom(this->idSocket, buf, len, 0, (struct sockaddr *) sockaddrs, 
               (socklen_t*)&size);

   /*if (st == -1) {
      perror("Error al recibir mensaje\n");
      exit(2);
   }*/

   return st;

}