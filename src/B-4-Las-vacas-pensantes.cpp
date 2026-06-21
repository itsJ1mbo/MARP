/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
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
int vacas_rec(const vector<int>& cubos, int i, int j, Matriz<int>& comida, bool t) 
{
    int& res = comida[i][j];
    if (res == -1) 
    {
        if (i > j) res = 0;
        else if (i == j) res = t ? cubos[i] : 0;
        else if (!t)
            if (cubos[i] > cubos[j])
                res = vacas_rec(cubos, i + 1, j, comida, !t);
			else
				res = vacas_rec(cubos, i, j - 1, comida, !t);
        else
            res = max(
            	vacas_rec(cubos, i + 1, j, comida, !t) + cubos[i],
                vacas_rec(cubos, i, j - 1, comida, !t) + cubos[j]
            );
    }

    return res;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (N == 0)  // fin de la entrada
        return false;

    vector<int> cubos(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> cubos[i];
    }

    Matriz<int> comida(N, N, -1);
	cout << vacas_rec(cubos, 0, N - 1, comida, true) << "\n";

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
