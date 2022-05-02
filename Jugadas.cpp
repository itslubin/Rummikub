#include "Jugadas.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool comprobarFicha(const tJugada& jugada, const tFicha& ficha) { //Comprueba si la ficha recibida se puede colocar en la jugada recibida
	bool colocar = true;
	int i = 0;
	if (comprobarSerie(jugada)) { //Si la jugada es una serie
		for (int i = 0; i < jugada.num_fichas; i++) {
			if (ficha.color == jugada.jugada[i].color || ficha.num != jugada.jugada[i].num) { //Si se repite el color o los numeros no son iguales la ficha no cumple la condicion de serie
				colocar = false;
			}
		}
	}
	else if (comprobarEscalera(jugada)) { //Si la jugada es una escalera
		if (ficha.color == jugada.jugada[jugada.num_fichas - 1].color) { //Si la ficha cumple la condicion basica de escalera
			if (jugada.jugada[0].num - ficha.num != 1 || ficha.num - jugada.jugada[jugada.num_fichas - 1].num != 1) {//No cumple la condicion segunda diferencia entre dos fichas == 1
				colocar = false;
			}
		}
		else { colocar = false; } //No cumple la condicion basica de escalera
	}
	return colocar;
}

bool haySerie(tSoporte& soporte) { //Comprueba si se pueden formar mas series con el soporte existente 
	bool hay_serie = false;
	int i = 1;
	ordenarPorNum(soporte);
	tJugada posible_serie; //Inicializacion de las variables e inclusion de la primera ficha del soporte en el array temporal
	iniJugada(posible_serie);
	posible_serie.num_fichas = 0;
	posible_serie.jugada[posible_serie.num_fichas] = soporte.fichas[0];
	posible_serie.num_fichas++;
	while (!hay_serie && i < soporte.cont) {
		if (posible_serie.jugada[posible_serie.num_fichas - 1].num == soporte.fichas[i].num && posible_serie.jugada[posible_serie.num_fichas - 1].color != soporte.fichas[i].color) {
			posible_serie.jugada[posible_serie.num_fichas] = soporte.fichas[i];
			posible_serie.num_fichas++;
			if (posible_serie.num_fichas > COLORES / 2 && i == soporte.cont - 1) { //Si encontramos una serie salimos del bucle
				hay_serie = true;
			}
		}
		else if (posible_serie.jugada[posible_serie.num_fichas - 1].num != soporte.fichas[i].num) {
			if (posible_serie.num_fichas > COLORES / 2) { //Si encontramos una serie salimos del bucle
				hay_serie = true;
			}
			//Cada vez que cambie el numero vaciamos el array y metemos el nuevo elemento
			posible_serie.num_fichas = 0;
			posible_serie.jugada[posible_serie.num_fichas] = soporte.fichas[i];
			posible_serie.num_fichas++;
		}
		i++;
	}
	delete[] posible_serie.jugada; //Al ser una jugada auxilar la eliminamos tras su uso
	return hay_serie;
}

bool hayEscalera(tSoporte& soporte) { //Comprueba si se pueden formar mas escaleras con el soporte existente
	bool hay_escalera = false;
	int i = 1;
	ordenarPorColor(soporte);
	tJugada posible_escalera; //Inicializacion de las variables e inclusion de la primera ficha del soporte en el array temporal
	iniJugada(posible_escalera);
	posible_escalera.num_fichas = 0;
	posible_escalera.jugada[posible_escalera.num_fichas] = soporte.fichas[0];
	posible_escalera.num_fichas++;
	while (!hay_escalera && i < soporte.cont) {
		if (soporte.fichas[i].num - posible_escalera.jugada[posible_escalera.num_fichas - 1].num == 1 && posible_escalera.jugada[posible_escalera.num_fichas - 1].color == soporte.fichas[i].color) {
			posible_escalera.jugada[posible_escalera.num_fichas] = soporte.fichas[i];
			posible_escalera.num_fichas++;
			if (posible_escalera.num_fichas > COLORES / 2 && i == soporte.cont - 1) { //Si encontramos una escalera salimos del bucle
				hay_escalera = true;
			}
		}
		else if (posible_escalera.jugada[posible_escalera.num_fichas - 1].color != soporte.fichas[i].color) { //Si el color es distinto reseteamos directamente
			if (posible_escalera.num_fichas > COLORES / 2) { //Si encontramos una escalera salimos del bucle
				hay_escalera = true;
			}
			//Cada vez que cambie el color o la diferencia entre los numeros no sea uno, vaciamos el array y metemos el nuevo elemento
			posible_escalera.num_fichas = 0;
			posible_escalera.jugada[posible_escalera.num_fichas] = soporte.fichas[i];
			posible_escalera.num_fichas++;
		} //Sin embargo si no cumple la condicion de la direncia, seguimos buscando sin resetear hasta un cambio de color o final
		i++;
	}
	delete[] posible_escalera.jugada; //Al ser una jugada auxilar la eliminamos tras su uso
	return hay_escalera;
}

bool ponerFicha(tJugada& jugada, tFicha& ficha) { //Recibe una jugada y una ficha y comprueba si se puedo colocar la ficha en la jugada. Devuelve true si es posible y false en caso contrario
	bool ok = true;
	int i = 0;
	if (comprobarSerie(jugada)) { //Si la jugada es una serie
		for (int i = 0; i < jugada.num_fichas; i++) {
			if (ficha.color == jugada.jugada[i].color || ficha.num != jugada.jugada[i].num) { //Si se repite el color o los numeros no son iguales la ficha no cumple la condicion de serie
				ok = false;
			}
		}
		if (ok) { //Si se han cumplido la condicion de la ficha la aniadimos a la jugada
			jugada.jugada[jugada.num_fichas] = ficha;
			jugada.num_fichas++;
		}
	}
	else if (comprobarEscalera(jugada)) { //Si la jugada es una escalera
		if (ficha.color == jugada.jugada[jugada.num_fichas - 1].color) { //Si la ficha cumple la condicion basica de escalera
			if (ficha.num - jugada.jugada[jugada.num_fichas - 1].num == 1) { //Aniadir ficha al final
				jugada.jugada[jugada.num_fichas] = ficha;
				jugada.num_fichas++;
			}
			else if (jugada.jugada[0].num - ficha.num == 1) { //Aniadir ficha al principio
				for (int i = jugada.num_fichas; i > 0; i--) { //Desplazamos todas las fichas una posicion a la derecha
					jugada.jugada[i] = jugada.jugada[i - 1];
				}
				jugada.jugada[0] = ficha;
				jugada.num_fichas++;
			}
			else { ok = false; } //No cumple la condicion segunda diferencia entre dos fichas == 1
		}
		else { ok = false; } //No cumple la condicion basica de escalera
	}
	return ok;
}

int nuevaJugada(tSoporte& soporte, tJugada& jugada) { //Permite al usuario crear una jugada con fichas que haya en su soporte
	iniJugada(jugada);
	mostrar(soporte);
	mostrarIndices(soporte.cont);
	return lecturaIndices(soporte, jugada);
}

int lecturaIndices(const tSoporte& soporte, tJugada& jugada) { //Recibe el soporte de un jugador y colaca las fichas que indica el usuario en una jugada
	int indices;
	cout << setw(4) << " ";
	cout << "Fichas (0 al final): ";
	cin >> indices;
	while (indices != 0) { //0 actua como un centinela final
		if (indices > soporte.cont || indices < 0) { //Para evitar excepciones si introduce indices invalidos volvemos al menu 
			cout << "\nIndices invalidos" << endl;
			jugada.num_fichas = 0;
			indices = 0;
		}
		else {
			jugada.jugada[jugada.num_fichas] = soporte.fichas[indices - 1];
			jugada.num_fichas++;
		}
		cin >> indices;
	}
	return jugada.num_fichas;
}

void mostrarIndices(int longitud) { //Muestra los indices de las fichas comenzando por 1 
	cout << setw(8) << " ";
	for (int i = 0; i < longitud; i++) { cout << setw(2) << i + 1 << "  "; }
	cout << endl << endl;
}

bool comprobarSerie(const tJugada& jugada) { //Recibe una jugada y comprueba si dicha jugada es una serie correcta
	bool ok = true;
	int i = 0;
	while (ok && i < jugada.num_fichas - 1) { //Recorrido por la jugada mientras esta sea correcta
		if (jugada.jugada[i].num != jugada.jugada[i + 1].num || jugada.jugada[i].color == jugada.jugada[i + 1].color || jugada.num_fichas >= COLORES + 1) { //Si no cumple la condicion devolvemos false
			ok = false;
		}
		i++;
	}
	return ok;
}

bool comprobarEscalera(const tJugada& jugada) { //Recibe una jugada y comprueba si dicha jugada es una escalera correcta
	bool ok = true;
	int i = 0;
	while (ok && i < jugada.num_fichas - 1) { //Recorrido por la jugada mientras esta sea correcta
		if (jugada.jugada[i].color != jugada.jugada[i + 1].color || (jugada.jugada[i + 1].num - jugada.jugada[i].num) != 1) { //Si no cumple la condicion devolvemos false
			ok = false;
		}
		i++;
	}
	return ok;
}

void eliminaFichas(tSoporte& soporte, const tJugada& jugada) { //Recibe el soporte de un jugador y una jugada, elimina del soporte las fichas que hay en la jugada
	bool eliminado;
	int j;
	for (int i = 0; i < jugada.num_fichas; i++) { //Recorrido por la jugada realizada
		eliminado = false;
		j = 0;
		while (!eliminado && j < soporte.cont) { //Recorrido por el soporte del jugador hasta encontrar y eliminar la ficha correspondiente
			if (soporte.fichas[j].num == jugada.jugada[i].num && soporte.fichas[j].color == jugada.jugada[i].color) { //Si encontramos la ficha que buscamos a eliminar
				for (int k = j; k < soporte.cont - 1; k++) { //Eliminamos la ficha
					soporte.fichas[k] = soporte.fichas[k + 1];
				}
				soporte.cont--;
				eliminado = true;
			}
			j++;
		}
		if (soporte.capacidad - soporte.cont >= 8) {
			tPtrFicha aux = new tFicha[soporte.capacidad - CAPACIDAD / 2];
			soporte.capacidad -= CAPACIDAD / 2;
			for (int i = 0; i < soporte.capacidad; i++) { //Copia de los elementos del array antiguo en el nuevo array de menor tamanio
				aux[i] = soporte.fichas[i];
			}
			delete soporte.fichas; //Liberamos del monton el array antiguo
			soporte.fichas = aux; //Apuntamos al nuevo array
		}
	}
	
}

void mostrar(const tJugada& jugada) { //Muestra una jugada con su correspondiente color
	for (int i = 0; i < jugada.num_fichas; i++) {
		mostrar(jugada.jugada[i]);
	}
	colorTexto(BLANCO);
}

void mostrarSeries(const tSoporte& soporte) { //Muestra las posibles series 
	tJugada posible_serie; //Inicializacion de las variables e inclusion de la primera ficha del soporte en el array temporal
	iniJugada(posible_serie);
	posible_serie.num_fichas = 0;
	posible_serie.jugada[posible_serie.num_fichas] = soporte.fichas[0];
	posible_serie.num_fichas++;
	for (int i = 1; i < soporte.cont; i++) { //Comparamos con los elementos restantes
		if (posible_serie.jugada[posible_serie.num_fichas - 1].num == soporte.fichas[i].num && posible_serie.jugada[posible_serie.num_fichas - 1].color != soporte.fichas[i].color) {
			posible_serie.jugada[posible_serie.num_fichas] = soporte.fichas[i];
			posible_serie.num_fichas++;
			if (posible_serie.num_fichas > COLORES / 2 && i == soporte.cont - 1) { //Para mostrar la serie si cumple la condicion al final del soporte
				mostrar(posible_serie);
				cout << endl;
			}
		}
		else if (posible_serie.jugada[posible_serie.num_fichas - 1].num != soporte.fichas[i].num) {
			if (posible_serie.num_fichas > COLORES / 2) { //Mostramos las series ,si cumplen la condicion, pudiendo haber mas posibles series en el soporte
				mostrar(posible_serie);
				cout << endl;
			}
			//Cada vez que cambie el numero vaciamos el array y metemos el nuevo elemento
			posible_serie.num_fichas = 0;
			posible_serie.jugada[posible_serie.num_fichas] = soporte.fichas[i];
			posible_serie.num_fichas++;
		}
	}
	delete[] posible_serie.jugada; //Al ser una jugada auxilar la eliminamos tras su uso
}

void mostrarEscaleras(const tSoporte& soporte) { //Muestra las posibles escaleres 
	tJugada posible_escalera; //Inicializacion de las variables e inclusion de la primera ficha del soporte en el array temporal
	iniJugada(posible_escalera);
	posible_escalera.num_fichas = 0;
	posible_escalera.jugada[posible_escalera.num_fichas] = soporte.fichas[0];
	posible_escalera.num_fichas++;
	for (int i = 1; i < soporte.cont; i++) { //Comparamos con los elementos restantes
		if (soporte.fichas[i].num - posible_escalera.jugada[posible_escalera.num_fichas - 1].num == 1 && posible_escalera.jugada[posible_escalera.num_fichas - 1].color == soporte.fichas[i].color) {
			posible_escalera.jugada[posible_escalera.num_fichas] = soporte.fichas[i];
			posible_escalera.num_fichas++;
			if (posible_escalera.num_fichas > COLORES / 2 && i == soporte.cont - 1) { //Mostramos las posibles escaleras, si cumplen la condicion, ya al final del soporte
				mostrar(posible_escalera);
				cout << endl;
			}
		}
		else if (posible_escalera.jugada[posible_escalera.num_fichas - 1].color != soporte.fichas[i].color) { //Si el color es distinto reseteamos directamente
			if (posible_escalera.num_fichas > COLORES / 2) { //Mostramos las escaleras , si cumplen la condicion, pudiendo haber mas posibles escaleras en el soporte
				mostrar(posible_escalera);
				cout << endl;
			}
			//Cada vez que cambie el color o la diferencia entre los numeros no sea uno, vaciamos el array y metemos el nuevo elemento
			posible_escalera.num_fichas = 0;
			posible_escalera.jugada[posible_escalera.num_fichas] = soporte.fichas[i];
			posible_escalera.num_fichas++;
		} //Sin embargo si no cumple la condicion de la direncia, seguimos buscando sin resetear hasta un cambio de color o final
	}
	delete[] posible_escalera.jugada; //Al ser una jugada auxilar la eliminamos tras su uso
}

void iniJugada(tJugada& jugada) { //Crea el array dinámico e inicializa su contador a 0
	jugada.jugada = new tFicha[MAX_FICHAS + 1];
	jugada.num_fichas = 0;
}