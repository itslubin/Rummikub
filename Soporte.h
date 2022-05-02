#ifndef soporte_h
#define soporte_h

#include "Fichas.h"

const int CAPACIDAD = 8; //Capacidad inicial que tiene el soporte de un jugador 

struct tSoporte { //Soporte de un jugador
	tPtrFicha fichas = nullptr;
	int cont, capacidad;
};

void mostrar(const tSoporte& soporte); //Muestra por pantalla el soporte de un jugador
void ordenarPorNum(tSoporte& soporte); //Ordena el soporte del jugador por numeros de menor a mayor mediante el metodo de burbuja
void ordenarPorColor(tSoporte& soporte); //Ordena el soporte del jugador por colores de menor a mayor mediante el metodo de burbuja
void iniSoporte(tSoporte& soporte); //Inicializa cada soporte con un array dinámico de capacidad para 8 fichas
void nuevaFicha(tSoporte& soporte); //A la hora de aniadir o eliminar la ficha ajusta el array dinamico a sus dimensiones adecuadas

#endif
