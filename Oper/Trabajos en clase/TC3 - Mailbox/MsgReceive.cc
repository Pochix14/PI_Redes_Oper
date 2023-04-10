#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Mailbox.h"
#define MAXDATA 1024

int main( int argc, char ** argv ) {


   //struct msgbuf {
      long type;   // this field must exist at first place
      char data[ MAXDATA ];        // char array for simplicity
      // user can define other fields
   //} A;
   int id, size, st;
   MailBox m;

   
   st = m.recv( 2023, (void *)data, MAXDATA );  // Receives a message with 2023 type
   while ( st > 0 ) {
      printf("%s\n", data);
      st = m.recv( 2023, (void *)data, MAXDATA);
   }

}