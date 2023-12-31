#include <vector>
#include <string>

#include "clases.h"

using std::string;
using std::vector;

#ifndef CARTAS_H
#define CARTAS_H

// --- Funciones
bool esUnAs(int carta);
void puntajeCarta(int carta, int *numeroAsParticipante, int *sumaCartasParticipante, bool *outParticipante);
void imprimirCarta(bool nuevaLinea, int carta);
void chequearMazo(vector<int> *mazo, int *cartasUsadas, int *numeroMazo);
int revolverCarta(int numero, vector<int>*mazo, int *cartasUsadas, int *numeroMazo);
void mensajeFinal(string mensaje);

#endif