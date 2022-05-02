#ifndef bolsa_h
#define bolsa_h

#include "Fichas.h"

const int  MAX_FILAS = COLORES * 2; //Existen dos fichas del mismo color

struct tBolsa { //Tamanio maximo de la matriz es de MAX_FILAS = 8 * MAX_FICHAS = 13
	tPtrFicha matriz[MAX_FILAS][MAX_FICHAS]; //Matriz de dos dimensiones formadas por punteros que apuntan a fichas creadas en el monton 
	int NumFichas, max_fichas;
};


void inicializarBolsa(tBolsa& bolsa); //Se trata de un procedimiento que inicializa los valores de la bolsa
tFicha robar(tBolsa& bolsa); //Procedimiento de busqueda en la bolsa mientras queden fichas de un puntero no nulo
void mostrar(const tBolsa& bolsa); //Se trata de un procedimiento que muestra los valores de la bolsa con su correspondiente color
void delBolsa(tBolsa& bolsa); //Libera la  memoria dinamica de las fichas que todavia queden en la bolsa al final del programa

#endif 
