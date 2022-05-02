#include "Bolsa.h"
#include <iostream>

using namespace std;

void inicializarBolsa(tBolsa& bolsa) { //Se trata de un procedimiento que inicializa los valores de la bolsa
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < bolsa.NumFichas; j++) {
			bolsa.matriz[i][j] = new tFicha;  //Creamos una ficha en el monton para posterirmente asignarle el valor
			bolsa.matriz[i][j]->num = j + 1;
			bolsa.matriz[i][j]->color = tColor(i % 4);
		}
	}
	bolsa.max_fichas = MAX_FILAS * bolsa.NumFichas; //Numero de fichas que tiene la bolsa en total
}

tFicha robar(tBolsa& bolsa) { //Procedimiento de busqueda en la bolsa mientras queden fichas de un puntero no nulo
	tFicha ficha; //Si no quedan fichas libres en la bolsa devuelve una fiche libre con - 1
	int fila, col;
	fila = rand() % MAX_FILAS;
	col = rand() % bolsa.NumFichas;
	while (bolsa.matriz[fila][col] == nullptr && bolsa.max_fichas != 0) { //Siempre que queden fichas en la bolsa buscamos un puntero no nulo (apunta a alguna ficha)
		if (col < bolsa.NumFichas - 1) { col++; } 	// Mientras no se haya llegado al final de la fila, vamos aumentando las columnas
		else { //col == bolsa.NumFichas - 1 (final de la columna)
			col = 0;
			if (fila != MAX_FILAS - 1) { fila++; } //Incrementamos la fila siempre y cuando no estemos en la ultima 
			else { fila = 0; } //Si estamos en la ultima fila volvemos al principio
		}
	}
	if (bolsa.matriz[fila][col] != nullptr) { //Se encuentra un puntero no nulo
		ficha = *bolsa.matriz[fila][col]; //Robamos la ficha 
		bolsa.max_fichas--;
		delete bolsa.matriz[fila][col]; //Liberamos la memoria
		bolsa.matriz[fila][col] = nullptr; // Y la eliminamos
	}
	return ficha;
}

void mostrar(const tBolsa& bolsa) { //Se trata de un procedimiento que muestra los valores de la bolsa con su correspondiente color
	tFicha ficha_libre;
	cout << "Bolsa..." << endl;
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < bolsa.NumFichas; j++) {
			if (bolsa.matriz[i][j] != nullptr) { mostrar(*bolsa.matriz[i][j]); }
			else { mostrar(ficha_libre); }
		}
		cout << endl;
	}
	cout << endl;
	colorTexto(BLANCO);
}

void delBolsa(tBolsa& bolsa) { //Libera la  memoria dinamica de las fichas que todavia queden en la bolsa al final del programa
	for (int i = 0; i < MAX_FILAS; i++) {
		for (int j = 0; j < bolsa.NumFichas; j++) {
			if (bolsa.matriz[i][j] != nullptr) {
				delete bolsa.matriz[i][j];
			}
		}
	}
}