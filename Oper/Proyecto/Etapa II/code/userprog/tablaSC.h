#ifndef TABLA_SC
#define TABLA_SC

#include "bitmap.h"

#define MAX_FILES 20

class TablaSC {
public:
  TablaSC();       // Initialize 
  ~TablaSC();      // De-allocate

  int Open(void* UnixHandle); // Register the file handle
  int Close(int NachosHandle);      // Unregister the file handle
  bool is_opened(int NachosHandle);
  void* get_unix_handle(int NachosHandle);
  int get_current_index();
  void add_thread();	// If a user thread is using this table, add it
  void del_thread();		// If a user thread is using this table, delete it

  void print();               // Print contents

private:
  void** openFiles;		// A vector with user opened files
  BitMap* openFilesMap;	// A bitmap to control our vector
  int usage;
  int current_index; 		// How many threads are using this table
  int max_length;
  int current_length;
  };
#endif