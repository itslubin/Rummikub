#ifndef fichas_h
#define fichas_h

#include "Colores.h"

const int MAX_FICHAS = 13; //Maximo numero de fichas de un color

struct tFicha { //Cada ficha esta formada por un numero y un color
	int num = -1;
	tColor color = LIBRE;
};

typedef tFicha* tPtrFicha; //tPtrFicha es un puntero que apunta a una ficha creada en memoria dinamica

void mostrar(const tFicha& ficha); //Recibe los datos de una ficha y muestra la ficha con su correspondiente color 

#endif
