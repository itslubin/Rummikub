#ifndef soportes_h
#define soportes_h

#include "Soporte.h"
#include "Bolsa.h"

const int MAX_JUGADORES = 4;

struct tSoportes { //Contiene todos los soportes de los jugadores 
	tSoporte soporte[MAX_JUGADORES]; //Cada elemento del array contiene el soporte de un jugador
	int IniFichas, NumJugadores;
};

void inicializarDatosJuego(tBolsa& bolsa, tSoportes& soportes, int& activo); /// //Inicializa los datos para comenzar el juego
void repartir(tBolsa& bolsa, tSoportes& soportes); //Reparte las fichas iniciales de los jugadores, muestra sus soportes y la bolsa actualizada 
void ganadorBloqueo(const tSoportes& soportes); /// //Busca el ganador en caso de que haya un bloqueo (bolsa sin fichas y jugadores que no pueden poner mas fichas)
void delSoportes(tSoportes& soportes); //Libera la memoria dinamica utilizada por el array dinamico que contiene las fichas de un jugador

#endif
