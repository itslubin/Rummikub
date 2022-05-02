#include "Tablero.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool comprobarBloqueo(const tTablero& tablero, tSoporte& soporte) { //Comprueba si el jugador aun puede poner ficha en el tablero para decidir si esta en bloqueo 
	bool bloqueo = true;
	int j, i = 0;
	//Comprueba si las fichas que quedan se pueden incorporar al tablero
	while (i < tablero.num_jugadas && !bloqueo) {//Recorrido por las jugadas del tablero
		j = 0;
		while (j < soporte.cont && !bloqueo) {//Recorrido por las fichas del soporte
			if (comprobarFicha(tablero.tablero[i], soporte.fichas[j])) { //Si aun se pueden incorporar fichas al tablero no se puede pasar el turno
				bloqueo = false;
			}
			j++;
		}
		i++;
	}
	//Comprueba si las fichas que quedan pueden formar nuevas series o escaleras 
	if (haySerie(soporte) || hayEscalera(soporte)) {
		bloqueo = false;
	}
	return bloqueo;
}

bool jugar(tTablero& tablero, tSoporte& soporte) { //Lleva acabo el juego de un turno, si realiza una jugada (pone fichas en el tablero) devuelve true, en caso contrario false
	bool jugada = false, correcto = false;
	int fichas_colocadas, op;
	fichas_colocadas = nuevaJugada(soporte, tablero.tablero[tablero.num_jugadas]);
	cout << endl;
	cout << "Jugada: ";
	mostrar(tablero.tablero[tablero.num_jugadas]);
	if (fichas_colocadas >= COLORES / 2 + 1) { //Si intenta colocar 3 fichas o mas
		cout << " ";
		if (comprobarSerie(tablero.tablero[tablero.num_jugadas]) || comprobarEscalera(tablero.tablero[tablero.num_jugadas])) { //Si es una serie o escalera
			jugada = true;
			eliminaFichas(soporte, tablero.tablero[tablero.num_jugadas]);
			if (comprobarSerie(tablero.tablero[tablero.num_jugadas])) { cout << "- Serie correcta!" << endl; }
			else { cout << "- Escalera correcta!" << endl; }
			tablero.num_jugadas++;
		}
		else {
			cout << "- No es una jugada correcta! Prueba de nuevo..." << endl; 
			delete tablero.tablero[tablero.num_jugadas].jugada;
		} //Si no es nada no aniadimos la jugada al tablero luego la eliminamos del monton
	}
	else if (fichas_colocadas == 1 && tablero.num_jugadas > 0) { //Ficha independiente a colocar en una jugada existente del tablero siempre que hayan jugadas
		cout << endl;
		while (!correcto) { //Mientras no introduzca una jugada correcta 
			cout << "Jugadas del tablero donde poner la ficha: ";
			cin >> op;
			if (op <= 0 || op > tablero.num_jugadas) {
				cout << "Jugada no existe. Prueba de nuevo ... \n";
			}
			else { correcto = true; }
		}
		if (ponerFicha(tablero.tablero[op - 1], tablero.tablero[tablero.num_jugadas].jugada[0])) { //Si es una jugada valida, entonces lo incluimos en la jugada
			jugada = true;
			cout << "  -> Colocada!" << endl;
			eliminaFichas(soporte, tablero.tablero[op - 1]);
		}
		else { cout << "La ficha introducida no se puede colocar en la jugada " << op << endl; } //Si no es una jugada valida no hacemos nada
	}
	else { cout << " - No se puede colocar la jugada! Prueba de nuevo..." << endl; } //Si intenta colocar dos fichas
	cout << endl;
	mostrar(tablero);
	mostrar(soporte);
	cout << endl;
	return jugada;
}

void mostrar(const tTablero& tablero) { //Muestra las jugadas que hay en el tablero con su correspondiente color
	cout << "Tablero:" << endl;
	if (tablero.num_jugadas == 0) { cout << "No hay jugadas" << endl; } //En caso de que no haya ninguna jugada, solo nos muestra una frase
	else { //En caso de que si haya jugadas
		for (int i = 0; i < tablero.num_jugadas; i++) { //Recorrido del tablero
			colorTexto(BLANCO);
			cout << " " << i + 1 << ": ";
			for (int j = 0; j < tablero.tablero[i].num_fichas; j++) { //Recorrido por la jugada
				mostrar(tablero.tablero[i].jugada[j]);
			}
			cout << endl;
		}
		colorTexto(BLANCO);
	}
	cout << endl;
}

void delTablero(tTablero& tablero) { //Libera la memoria dinámica de las jugadas que se hayan ido añadiendo al tablero
	for (int i = 0; i < tablero.num_jugadas; i++) {
		delete tablero.tablero[i].jugada;
	}
}


void delDatosJuego(tBolsa& bolsa, tSoportes& soportes, tTablero& tablero) { //Libera la  memoria dinamica al final del programa
	delBolsa(bolsa);
	delSoportes(soportes);
	delTablero(tablero);
}