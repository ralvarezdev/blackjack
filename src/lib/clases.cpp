#include <iostream>
#include <string>

#include "cartas.h"
#include "clases.h"
#include "terminal.h"

using std::cout;
using std::string;

// Método para eliminar los elementos del vector, asignar valor 0 a los enteros, y falso a los booleanos
void Mesa::reiniciarDatos()
{
    cartas.clear();
    out = numeroAs = sumaCartas = 0;
}

void Jugador::reiniciarDatos()
{
    cartas.clear();
    out = stand = ganador = empate = numeroAs = sumaCartas = 0;
}

// Metodo que imprime la apuesta y dinero de cada jugador
void Tablero::imprimirStats(string titulo, vector<int> *apuestas, vector<Jugador> *jugadoresStats)
{
    encabezado(titulo);
    cout << "\nRonda: " << ronda << "\t| Apuesta inicial: " << apuestaInicial << "\t| Mazos: "
         << numeroMazo << "\n"
         << string(65, '-');

    for (int x = 0; x < numeroJugadores; x++)
    {
        int dinero = (*jugadoresStats)[x].dinero;

        cout << "\nJugador " << x + 1;
        if ((*jugadoresStats)[x].bancarrota)
            cout << "\t| BANCARROTA\t\t|";
        else
        {
            cout << "\t| Dinero: " << dinero;

            if (apuestaInicial != 0 && dinero != 0)
                cout << "\t\t| Apuesta: " << (*apuestas)[x];
            else if (dinero == 0)
                cout << "\t\t| Apuesta: " << (*apuestas)[x] << " ALL-IN";
        }
    }
}

// Método que imprime las cartas de un jugador en específico
void Tablero::imprimirCartas(int n, vector<int> *cartas, int *sumaCartas)
{
    cout << "\n\n*** Cartas del jugador " << n + 1 << " ***";
    for (int x = 0; x < (*cartas).size(); x++)
        imprimirCarta(true, (*cartas)[x]);

    cout << "\nTotal: " << *sumaCartas;
}

// Método que imprime las cartas de todos los jugadores
void Tablero::imprimirTablero(vector<Jugador> *jugadoresStats)
{
    bool imprimirMas;
    int x, y, n, numeroJugadores, carta, filas, filasCartas, columnas;
    string separacion;
    vector<int> cantidadCartas;

    numeroJugadores = (*jugadoresStats).size();
    filas = (numeroJugadores % 4 != 0) ? numeroJugadores / 4 + 1 : numeroJugadores / 4;

    separacion = string((numeroJugadores >= 4) ? 17 * 4 : 17 * numeroJugadores - 5, '-');

    for (x = 0; x < filas; x++)
    {
        imprimirMas = true;
        filasCartas = 0;
        cantidadCartas.clear();
        columnas = ((numeroJugadores - 4 * x) >= 4) ? 4 : numeroJugadores - (4 * x);

        cout << "\n"
             << separacion << "\n";
        for (y = 0; y < columnas; y++)
        {
            n = 4 * x + y;
            cantidadCartas.push_back((*jugadoresStats)[n].cartas.size());

            cout << "Jug " << n + 1;
            if ((*jugadoresStats)[n].out && (*jugadoresStats)[n].sumaCartas <= 21)
                cout << " [Ret]";
            else if ((*jugadoresStats)[n].ganador)
                cout << " [Gan]";
            else if ((*jugadoresStats)[n].empate)
                cout << " [Emp]";
            else if (!(*jugadoresStats)[n].bancarrota)
                cout << " [Per]";
            else
                cout << " [Ban]";

            if (y != columnas - 1)
                cout << "\t| ";
        }

        while (imprimirMas)
        {
            for (y = 0; y < columnas; y++)
            {
                n = 4 * x + y;

                if (!(*jugadoresStats)[n].bancarrota)
                {
                    carta = (*jugadoresStats)[n].cartas[filasCartas];

                    if (filasCartas < cantidadCartas[y])
                        imprimirCarta((y == 0), carta);
                    else if (y == 0)
                        cout << "\n";
                }
                else if (y == 0 && filasCartas >= cantidadCartas[y])
                    cout << "\n";

                if (y != columnas - 1)
                    cout << "\t\t| ";
            }
            filasCartas++;

            for (y = 0; y < columnas; y++)
            {
                imprimirMas = (filasCartas < cantidadCartas[y]);
                if (imprimirMas)
                    break;
            }
        }

        for (y = 0; y < columnas; y++)
        {
            n = 4 * x + y;

            if ((*jugadoresStats)[n].bancarrota && y != 0)
                cout << "\t";
            else if (y == 0)
                cout << "\n";

            if (!(*jugadoresStats)[n].bancarrota)
                cout << "Total: " << (*jugadoresStats)[n].sumaCartas;
            else if (y == 0)
                cout << "\t";

            if (y != columnas - 1)
                cout << "\t| ";
        }
    }
    cout << "\n"
         << separacion;
}