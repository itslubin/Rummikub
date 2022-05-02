#include "Soporte.h"
#include <iostream>
using namespace std;

void mostrar(const tSoporte& soporte) { //Muestra por pantalla el soporte de un jugador
	cout << "Soporte:";
	for (int i = 0; i < soporte.cont; i++) { //Recorrido del soporte del jugador
		mostrar(soporte.fichas[i]);
	}
	cout << endl;
	colorTexto(BLANCO);
}

void ordenarPorNum(tSoporte& soporte) { //Ordena el soporte del jugador por numeros de menor a mayor mediante el metodo de burbuja
	bool inter = true;
	int i = 0;
	while ((i < soporte.cont - 1) && inter) { // Desde el primer elemento hasta el penúltimo o no haya que seguir
		inter = false;
		for (int j = soporte.cont - 1; j > i; j--) { // Desde el último hasta el siguiente a i
			// Si es el mismo numero pero distinto color tambien ordena segun el orden de los colores (segunda condicion)
			if (soporte.fichas[j].num < soporte.fichas[j - 1].num || (soporte.fichas[j].num == soporte.fichas[j - 1].num && soporte.fichas[j].color < soporte.fichas[j - 1].color)) {
				tFicha tmp;
				tmp = soporte.fichas[j];
				soporte.fichas[j] = soporte.fichas[j - 1];
				soporte.fichas[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) { i++; }
	}
}

void ordenarPorColor(tSoporte& soporte) { //Ordena el soporte del jugador por colores de menor a mayor mediante el metodo de burbuja
	bool inter = true;
	int i = 0;
	while ((i < soporte.cont - 1) && inter) { //Desde el primer elemento hasta el penúltimo o no haya que seguir
		inter = false;
		for (int j = soporte.cont - 1; j > i; j--) { //Desde el último hasta el siguiente a i
			//Si es el mismo color pero distinto numero tambien ordena segun el orden de los numeros (segunda condicion)
			if (soporte.fichas[j].color < soporte.fichas[j - 1].color || (soporte.fichas[j].color == soporte.fichas[j - 1].color && soporte.fichas[j].num < soporte.fichas[j - 1].num)) {
				tFicha tmp;
				tmp = soporte.fichas[j];
				soporte.fichas[j] = soporte.fichas[j - 1];
				soporte.fichas[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) { i++; }
	}
}
 
void iniSoporte(tSoporte& soporte) { //Inicializa cada soporte con un array dinámico de capacidad para 8 fichas
	soporte.capacidad = CAPACIDAD; //Inicializamos la capacidad del soporte
	soporte.fichas = new tFicha[CAPACIDAD]; //soporte.fichas apunta al array de fichas creado en el monton
	soporte.cont = 0;
}

void nuevaFicha(tSoporte& soporte) { //A la hora de aniadir o eliminar la ficha ajusta el array dinamico a sus dimensiones adecuadas
	if (soporte.cont == soporte.capacidad) {
		tPtrFicha aux = new tFicha[soporte.capacidad + CAPACIDAD];
		for (int i = 0; i < soporte.capacidad; i++) { //Copia de los elementos del array antiguo en el nuevo array ampliado
			aux[i] = soporte.fichas[i];
		}
		soporte.capacidad += CAPACIDAD;
		delete soporte.fichas; //Liberamos del monton el array antiguo
		soporte.fichas = aux; //Apuntamos al nuevo array
	}
}