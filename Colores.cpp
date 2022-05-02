#include "Colores.h"
#include <iostream>
using namespace std; 

void colorTexto(tColor color) { //Muestra por pantalla el color correspondiente de las fichas
	switch (color)
	{
	case AMARILLO:
		cout << "\033[1;40;33m";
		break;
	case AZUL:
		cout << "\033[40;34m";
		break;
	case ROJO:
		cout << "\033[40;31m";
		break;
	case VERDE:
		cout << "\033[40;32m";
		break;
	case BLANCO:
		cout << "\033[40;37m";
		break;
	case LIBRE:
		cout << "\033[40;37m";
		break;
	}
}