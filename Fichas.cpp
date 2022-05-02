#include "Fichas.h"
#include <iostream>
#include <iomanip>
using namespace std;

void mostrar(const tFicha& ficha) { //Recibe los datos de una ficha y muestra la ficha con su correspondiente color
	colorTexto(ficha.color);
	cout << right << setw(2) << ficha.num << "  ";
}