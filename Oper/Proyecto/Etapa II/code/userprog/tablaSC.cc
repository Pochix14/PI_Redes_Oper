#include "tablaSC.h"


TablaSC::TablaSC() {
	openFiles = new void* [MAX_FILES];
	//this->openFiles = (int*)calloc(MAX_FILES, sizeof(int)); 
	for (int i = 0; i < MAX_FILES; ++i) {
		openFiles[i] = NULL;
		}
	this->usage = 1;			//siempre hay como minimo un hilo/proceso usandola cuando se crea.  
	this->openFilesMap = new BitMap(MAX_FILES);
	this->max_length = MAX_FILES;
	this->current_length = 0;
	this->current_index = 0;
	int posicion = openFilesMap->Find();
	}


TablaSC::~TablaSC() {
	delete openFiles;
	//free(this->openFiles); 
	delete this->openFilesMap;
	}

int TablaSC::Open(void* unix_handle) {
	//printf("Estoy en open");
	int posicion = openFilesMap->Find();//Posicion para unix_handle en el openfiles.

	if (-1 == posicion) {
		printf("Error, no hay más espacio");
		}	
else {
		openFilesMap->Mark(posicion);
		this->openFiles[posicion] = unix_handle;
		current_index++;
		}

	return posicion;
	}

int TablaSC::Close(int nachos_handle) {
	int success = -1;
	if (is_opened(nachos_handle) && nachos_handle > 2) {
		openFilesMap->Clear(nachos_handle);
		openFiles[nachos_handle] = NULL;
		success = 0;
		}
	return success;

	}

int TablaSC::get_current_index() {
	return this->current_index;
	}


bool TablaSC::is_opened(int nachos_handle) {
	return openFilesMap->Test(nachos_handle);
	}

void* TablaSC::get_unix_handle(int nachos_handle) {
	void* unixHandle = NULL;
	if (is_opened(nachos_handle)) {
		unixHandle = openFiles[nachos_handle];
		}
	return unixHandle;
	}


void TablaSC::add_thread() {
	++this->usage;
	}


void TablaSC::del_thread() {
	if (this->usage == 1) {			//soy el ultimo thread, tengo que borrar todo. 
		//FALTA AGREGAR CÓDIGO.
		}
	else {
		--this->usage;
		}
	}


void TablaSC::print() {


	}
