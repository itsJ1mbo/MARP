/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
int resolver_rec(const Matriz<int>& tablero, Matriz<int>& suma, int i, int j, int n)
{
    if (i < 0 || j < 0 || j >= n) return 0;
    if (suma[i][j] == -1)
    {
        if (i == 0) suma[i][j] = tablero[i][j];
        else
        {
            int arriba_izq = resolver_rec(tablero, suma, i - 1, j - 1, n);
            int arriba = resolver_rec(tablero, suma, i - 1, j, n);
            int arriba_der = resolver_rec(tablero, suma, i - 1, j + 1, n);

            suma[i][j] = tablero[i][j] + max({ arriba_izq, arriba, arriba_der });
        }
    }

    return suma[i][j];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> tablero(N, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cin >> tablero[i][j];
        }
    }
    Matriz<int> suma(N, N, -1);

    int max = 0, k = 0;
    for (int i = 0; i < N; i++)
    {
        int a = resolver_rec(tablero, suma, N - 1, i, N);
        if (max < a)
        {
            max = a;
            k = i + 1;
        }
    }

    std::cout << max << ' ' << k << '\n';

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
