//Autores: Javier Zhou Zhu y Lubin Ye 

#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include<cstdlib>
#include "Colores.h"
#include "Fichas.h"
#include "Bolsa.h"
#include "Soporte.h"
#include "Soportes.h"
#include "Jugadas.h"
#include "Tablero.h"

using namespace std;

// Prototipos
int menu();
// Lleva a cabo el desarrollo de todo el juego, por ello se incluye en el programa principal
void jugarJuego(tTablero& tablero, tBolsa& bolsa, tSoportes& soportes, int& activo); ///

/////Funcion MAIN/////
int main() {
	srand(time(nullptr)); // Para usar numeros aleatorios
	tBolsa bolsa;
	tSoportes soportes;
	tTablero tablero;
	int activo; //activo = Turno del jugador que esta jugando
	inicializarDatosJuego(bolsa, soportes, activo); //Inicializacion de las variables del juego
	jugarJuego(tablero, bolsa, soportes, activo); //COMIENZA EL JUEGO//
	delDatosJuego(bolsa, soportes, tablero);
	_CrtDumpMemoryLeaks();
	return 0;
}

void jugarJuego(tTablero& tablero, tBolsa& bolsa, tSoportes& soportes, int& activo) { //Lleva a cabo todo el desarrollo del juego
	bool juego_correcto = false, fin = false, robar_ficha = true, hay_serie = false, hay_escalera = false;
	int jugadores_bloqueo = 0;
	cout << "Turno para el jugador " << activo << " ..." << endl << endl;
	mostrar(tablero);
	mostrar(soportes.soporte[activo - 1]);
	do
	{
		switch (menu()) { //Menu devuelve la opcion escogida por el jugador
		case 0:
			fin = true;
			break;
		case 1: //Muestra el soporte ordenado por numero
			ordenarPorNum(soportes.soporte[activo - 1]);
			mostrar(soportes.soporte[activo - 1]);
			break;
		case 2: //Muestra el soporte ordenado por color
			ordenarPorColor(soportes.soporte[activo - 1]);
			mostrar(soportes.soporte[activo - 1]);
			break;
		case 3: //Sugiere posibles series y escaleras
			ordenarPorNum(soportes.soporte[activo - 1]);
			mostrarSeries(soportes.soporte[activo - 1]);
			ordenarPorColor(soportes.soporte[activo - 1]);
			mostrarEscaleras(soportes.soporte[activo - 1]);
			mostrar(soportes.soporte[activo - 1]);
			cout << endl;
			break;
		case 4: //Pone fichas del soporte en el tablero
			juego_correcto = jugar(tablero, soportes.soporte[activo - 1]);
			if (juego_correcto) { //Cuando jugada es correcta no roba ficha y volvemos a reinciar los jugadores en bloqueo
				robar_ficha = false;
				jugadores_bloqueo = 0;
			}
			if (soportes.soporte[activo - 1].cont == 0) { //Si el jugador ha puesto todas sus fichas
				cout << "El jugador " << activo << " ha ganado!";
				fin = true;
			}
			break;
		case 5: //Pasa el turno al siguiente jugador
			if (robar_ficha) { // SI NO SE HA HECHO JUGADA, robamos una ficha y la metemos en el soporte del jugador
				nuevaFicha(soportes.soporte[activo - 1]); //Actualizamos la dimension del array dinamico si es necesario
				soportes.soporte[activo - 1].fichas[soportes.soporte[activo - 1].cont] = robar(bolsa);
				if (soportes.soporte[activo - 1].fichas[soportes.soporte[activo - 1].cont].color != LIBRE && soportes.soporte[activo - 1].fichas[soportes.soporte[activo - 1].cont].num != -1) { //Si robamos una ficha
					soportes.soporte[activo - 1].cont++;
					mostrar(soportes.soporte[activo - 1]);
				}
				else { //Si no se pueden robar mas fichas
					cout << "\n!! Ya no quedan mas fichas en la bolsa !! IMPOSIBLE ROBAR" << endl;
					if (comprobarBloqueo(tablero, soportes.soporte[activo - 1])) {
						jugadores_bloqueo++;
						if (jugadores_bloqueo == soportes.NumJugadores) { //Si se han bloqueado todos los jugadores
							ganadorBloqueo(soportes);
							fin = true;
						}
					}
					else { jugadores_bloqueo = 0; } //Puede poner fichas pero no las pone, igualmente no tendriamos a todos bloqueados
				}
			}
			cout << endl;
			if (!fin) { // Actualizar el jugador
				activo = (activo % soportes.NumJugadores) + 1;
				juego_correcto = false;
				robar_ficha = true;
				hay_serie = false;
				hay_escalera = false;
				cout << "Turno para el jugador " << activo << " ..." << endl << endl;
				mostrar(tablero);
				mostrar(soportes.soporte[activo - 1]);
				cout << endl;
			}

			break;
		default:
			cout << "Error switch";
			break;
		}
	} while (!fin);
}

int menu() { //Se trata de una funcion que ofrece al usuario las opciones a elegir en el juego y devuelve la opcion elegida
	int op;
	do
	{
		cout << "1: Ordenar por num., 2: Ordenar por color, 3: Sugerir, 4: Poner, 5: Sig.,  0: Fin >>>  ";
		cin >> op;
	} while (op < 0 && op > 5);
	return op;
}
