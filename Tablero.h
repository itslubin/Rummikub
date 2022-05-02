#ifndef tablero_h
#define tabler_h

#include "Jugadas.h"

const int MAX_JUGADAS = MAX_FICHAS * 2; //Maximo numero de jugadas que puede tener un tablero

struct tTablero {
	tJugada tablero[MAX_JUGADAS];
	int num_jugadas = 0;
};

bool comprobarBloqueo(const tTablero& tablero, tSoporte& soporte); /// //Comprueba si el jugador aun puede poner ficha en el tablero para decidir si esta en bloqueo 
bool jugar(tTablero& tablero, tSoporte& soporte); //Lleva acabo el juego de un turno, si realiza una jugada (pone fichas en el tablero) devuelve true, en caso contrario false
void mostrar(const tTablero& tablero); //Muestra las jugadas que hay en el tablero con su correspondiente color
void delTablero(tTablero& tablero); //Libera la memoria dinámica de las jugadas que se hayan ido añadiendo al tablero
void delDatosJuego(tBolsa& bolsa, tSoportes& soportes, tTablero& tablero); //Libera la  memoria dinamica al final del programa


#endif
