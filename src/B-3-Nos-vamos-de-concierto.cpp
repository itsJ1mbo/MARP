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
struct Festival { double grupos; int precio; };

double mochila_rec(vector<Festival> const& fest, int i, int j, Matriz<double>& mochila) 
{
    if (mochila[i][j] != -1) // subproblema ya resuelto
        return mochila[i][j];
    if (i == 0 || j == 0) mochila[i][j] = 0;
    else if (fest[i - 1].precio > j)
        mochila[i][j] = mochila_rec(fest, i - 1, j, mochila);
    else
        mochila[i][j] = max(mochila_rec(fest, i - 1, j, mochila),
            mochila_rec(fest, i - 1, j - fest[i - 1].precio, mochila)
            + fest[i - 1].grupos);
    return mochila[i][j];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int P, N;
    std::cin >> P >> N;

    if (!std::cin)  // fin de la entrada
        return false;

	vector<Festival> festivales(N);
    for (int i = 0; i < N; ++i)
    {
		cin >> festivales[i].grupos >> festivales[i].precio;
    }

    Matriz<double> mochila(N + 1, P + 1, -1);
	cout << mochila_rec(festivales, N, P, mochila) << "\n";

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
