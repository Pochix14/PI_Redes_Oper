#ifndef TABLA_H
#define TABLA_H

#include "bitmap.h"

#define MAX_FILES 20

class Tabla {
public:
  Tabla();       // Initialize 
  ~Tabla();      // De-allocate

  int Open(int UnixHandle); // Register the file handle
  int Close(int NachosHandle);      // Unregister the file handle
  bool is_opened(int NachosHandle);
  int get_unix_handle(int NachosHandle);
  int get_current_index();
  void add_thread();	// If a user thread is using this table, add it
  void del_thread();		// If a user thread is using this table, delete it

  void print();               // Print contents

private:
  int* openFiles;		// A vector with user opened files
  BitMap* openFilesMap;	// A bitmap to control our vector
  int usage;
  int current_index; 		// How many threads are using this table
  int max_length;
  int current_length;
  };
#endif

