/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
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
int multiplica_matrices(vector<int> const& D) 
{
    int n = D.size();
    Matriz<int> matrices(n, n, 0); 

    for (int d = 2; d < n; ++d) // recorre diagonales
        for (int i = 0; i < n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            matrices[i][j] = numeric_limits<int>::max();
            for (int k = i + 1; k < j; ++k) {
                int temp = matrices[i][k] + matrices[k][j] + 2 * (D[j] - D[i]);
                matrices[i][j] = std::min(temp, matrices[i][j]); // es mejor partir por k
            }
        }

    return matrices[0][n - 1];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int L, N;
    std::cin >> L >> N;

    if (L == 0 && N == 0)  // fin de la entrada
        return false;

	std::vector<int> cortes(N + 2);
	cortes[0] = 0; cortes[N + 1] = L;
	for (int i = 1; i <= N; ++i) 
    {
		std::cin >> cortes[i];
	}

	std::cout << multiplica_matrices(cortes) << "\n";

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
