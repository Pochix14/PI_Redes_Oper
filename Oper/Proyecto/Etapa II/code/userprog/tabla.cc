#include "tabla.h"


Tabla::Tabla() {
	openFiles = new int[MAX_FILES];
	//this->openFiles = (int*)calloc(MAX_FILES, sizeof(int)); 
	for (int i = 0; i < MAX_FILES; ++i) {
		openFiles[i] = -1;
		}
	this->usage = 1;			//siempre hay como minimo un hilo/proceso usandola cuando se crea.  
	this->openFilesMap = new BitMap(MAX_FILES);
	this->max_length = MAX_FILES;
	this->current_length = 0;
	this->current_index = 0;
	int posicion = openFilesMap->Find();
	posicion = openFilesMap->Find();
	posicion = openFilesMap->Find();
	}


Tabla::~Tabla() {
	delete openFiles;
	//free(this->openFiles); 
	delete this->openFilesMap;
	}

int Tabla::Open(int unix_handle) {
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

int Tabla::Close(int nachos_handle) {
	int success = -1;
	if (is_opened(nachos_handle) && nachos_handle > 2) {
		openFilesMap->Clear(nachos_handle);
		openFiles[nachos_handle] = -1;
		success = 0;
		}
	return success;

	}

int Tabla::get_current_index() {
	return this->current_index;
	}


bool Tabla::is_opened(int nachos_handle) {
	return openFilesMap->Test(nachos_handle);
	}

int Tabla::get_unix_handle(int nachos_handle) {
	int unixHandle = -1;
	if (is_opened(nachos_handle)) {
		unixHandle = openFiles[nachos_handle];
		}
	return unixHandle;
	}


void Tabla::add_thread() {
	++this->usage;
	}


void Tabla::del_thread() {
	if (this->usage == 1) {			//soy el ultimo thread, tengo que borrar todo. 
		//FALTA AGREGAR CÓDIGO.
		}
	else {
		--this->usage;
		}
	}


void Tabla::print() {


	}
