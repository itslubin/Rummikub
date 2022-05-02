#ifndef jugadas_h
#define jugadas_h

#include "Soportes.h"

struct tJugada { //Contiene las fichas puestas por un jugador
	tPtrFicha jugada;
	int num_fichas;
};

bool comprobarFicha(const tJugada& jugada, const tFicha& ficha); /// //Comprueba si la ficha recibida se puede colocar en la jugada recibida
bool haySerie(tSoporte& soporte); /// //Comprueba si se pueden formar mas series con el soporte existente 
bool hayEscalera(tSoporte& soporte); /// //Comprueba si se pueden formar mas escaleras con el soporte existente
bool ponerFicha(tJugada& jugada, tFicha& ficha); //Recibe una jugada y una ficha y comprueba si se puedo colocar la ficha en la jugada. Devuelve true si es posible y false en caso contrario
int nuevaJugada(tSoporte& soporte, tJugada& jugada); //Permite al usuario crear una jugada con fichas que haya en su soporte
int lecturaIndices(const tSoporte& soporte, tJugada& jugada); /// //Recibe el soporte de un jugador y colaca las fichas que indica el usuario en una jugada
void mostrarIndices(int longitud); /// //Muestra los indices de las fichas comenzando por 1
bool comprobarSerie(const tJugada& jugada); /// //Recibe una jugada y comprueba si dicha jugada es una serie correcta
bool comprobarEscalera(const tJugada& jugada); /// //Recibe una jugada y comprueba si dicha jugada es una escalera correcta
void eliminaFichas(tSoporte& soporte, const tJugada& jugada); //Recibe el soporte de un jugador y una jugada, elimina del soporte las fichas que hay en la jugada
void mostrar(const tJugada& jugada); //Muestra una jugada con su correspondiente color
void mostrarSeries(const tSoporte& soporte); //Muestra las posibles series 
void mostrarEscaleras(const tSoporte& soporte); //Muestra las posibles escaleres 
void iniJugada(tJugada& jugada); //Crea el array dinámico e inicializa su contador a 0



#endif
