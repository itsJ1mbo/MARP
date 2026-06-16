/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
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
vector<int> resolver(const std::vector<int>& sectores, int V)
{
    int n = sectores.size();
    vector<EntInf> monedas(V + 1, Infinito);
    monedas[0] = 0;
    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i) {
        for (int j = sectores[i - 1]; j <= V; ++j) {
            monedas[j] = min(monedas[j], monedas[j - sectores[i - 1]] + 1);
        }
    }

    vector<int> sol;
    if (monedas[V] != Infinito) {
        int i = n, j = V;
        while (j > 0) { // no se ha pagado todo
            if (sectores[i - 1] <= j && monedas[j] == monedas[j - sectores[i - 1]] + 1) {
                // tomamos una moneda de tipo i
                sol.push_back(sectores[i - 1]);
                j = j - sectores[i - 1];
            }
            else // no tomamos más monedas de tipo i
                --i;
        }
    }

    return sol;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, S;
    std::cin >> V >> S;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> sectores(S);
    for (int i = 0; i < S; i++)
    {
        std::cin >> sectores[i];
    }

    vector<int> sol = resolver(sectores, V);

    if (!sol.empty())
	{
		std::cout << sol.size() << ": ";
    	for (auto a : sol)
    		std::cout << a << " ";
    	std::cout << "\n";
	}
	else std::cout << "Imposible\n";

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
