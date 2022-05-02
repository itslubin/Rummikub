#include "Soportes.h"
#include<iostream>
#include<iomanip>
using namespace std;

void inicializarDatosJuego(tBolsa& bolsa, tSoportes& soportes, int& activo) { //Inicializa los datos para comenzar el juego
	cout << "Bienvenido a Rummikub!" << endl << endl;
	do
	{
		cout << "Elige el numero de fichas de cada color con las que quieres jugar (entre 8 y 13): ";
		cin >> bolsa.NumFichas;
	} while (bolsa.NumFichas < 8 || bolsa.NumFichas > 13);
	do
	{
		cout << "Elige el numero inicial de fichas de cada jugador (entre 6 y 14): ";
		cin >> soportes.IniFichas;
	} while (soportes.IniFichas < 6 || soportes.IniFichas > 14);
	do
	{
		cout << "Elige el numero de jugadores (entre 2 y 4): ";
		cin >> soportes.NumJugadores;
	} while (soportes.NumJugadores < 2 || soportes.NumJugadores > 4);
	inicializarBolsa(bolsa);
	cout << endl;
	mostrar(bolsa);
	cout << endl << "Repartir fichas\n" << endl;
	repartir(bolsa, soportes);
	activo = 1 + rand() % soportes.NumJugadores + 1 - 1; //Determinacion aleatoria del jugador que comienza a jugar
	cout << endl;
}

void repartir(tBolsa& bolsa, tSoportes& soportes) { //Reparte las fichas iniciales de los jugadores, muestra sus soportes y la bolsa actualizada  
	for (int i = 0; i < soportes.NumJugadores; i++) { //Inicializacion numero fichas iniciales de cada jugador y sus soportes1
		iniSoporte(soportes.soporte[i]);
	}
	for (int j = 0; j < soportes.NumJugadores; j++) { //Reparto de fichas para los jugadores (j de jugador)
		for (int f = 0; f < soportes.IniFichas; f++) { //f de ficha
			nuevaFicha(soportes.soporte[j]);
			soportes.soporte[j].fichas[f] = robar(bolsa);
			soportes.soporte[j].cont++;
		}
		mostrar(bolsa);
		cout << endl;
		mostrar(soportes.soporte[j]);
		cout << endl;
	}
}

void ganadorBloqueo(const tSoportes& soportes) { //Busca el ganador en caso de que haya un bloqueo (bolsa sin fichas y jugadores que no pueden poner mas fichas)
	int array[MAX_JUGADORES] = { 0,0,0,0 }, valor_total, min, ind = 1;
	for (int i = 0; i < soportes.NumJugadores; i++) { //Recorido por los diferentes soportes de cada jugador
		valor_total = 0;
		for (int j = 0; j < soportes.soporte[i].cont; j++) { //Recorrido por las fichas en el soporte de un jugador
			valor_total += soportes.soporte[i].fichas[j].num; //Suma de los valores de sus fichas
		}
		array[i] = valor_total; //Guardamos dicho valor en un array temporal
	}
	min = array[0];
	cout << endl;
	for (int i = 0; i < soportes.NumJugadores; i++) { //Buscamos el minimo de ese array temporal y guardamos el indice del valor minimo (jugador ganador)
		cout << "Valor del soporte del jugador " << i + 1 << " :" << array[i] << endl;
		if (array[i] < min) { //Buscamos el primer menor 
			ind = i + 1; //Ya que activo es una variable que comienza en 1 e i comienza en 0
			min = array[i];
		}
	}
	cout << endl << setw(35) << " " << "    El jugador " << ind << " ha ganado!";
}

void delSoportes(tSoportes& soportes) { //Libera la memoria dinamica utilizada por el array dinamico que contiene las fichas de un jugador
	for (int i = 0; i < soportes.NumJugadores; i++) {
		delete soportes.soporte[i].fichas;
	}
}