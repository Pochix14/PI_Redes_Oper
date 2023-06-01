#include "syscall.h"

int main() {
   int id;
   char a[ 1024 ];

   id = Socket( AF_INET_NachOS, SOCK_STREAM_NachOS );
   Connect( id, "163.178.104.187", 80 );
   Write( "GET / HTTP/1.0\r\n\r\n", 32, id );
   Read( a, 1024, id );
   Write( a, 1024, 1 );
   Close( id );

}

