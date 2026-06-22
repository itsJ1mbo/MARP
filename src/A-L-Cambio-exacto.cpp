/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
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
pair<int, EntInf> mochila_rec(vector<int> const& obj, int P)
{
    int max_moneda = 0;
    for (int m : obj) {
	    max_moneda = std::max(m, max_moneda);
    }
    int MAX_DINERO = P + max_moneda; 

    std::vector<EntInf> dp(MAX_DINERO + 1, Infinito);
    dp[0] = 0; 

    for (int i = 0; i < obj.size(); ++i) {
        for (int j = MAX_DINERO; j >= obj[i]; --j) {
            if (dp[j - obj[i]] != Infinito) {
                dp[j] = std::min(dp[j], dp[j - obj[i]] + 1);
            }
        }
    }

    for (int j = P; j <= MAX_DINERO; ++j) {
        if (dp[j] != Infinito) {
            return { j, dp[j] };
        }
    }

    return { -1, Infinito };
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int P, N;
    std::cin >> P >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> monedas(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> monedas[i];
    }

    pair<int, EntInf> sol = mochila_rec(monedas, P);

	std::cout << sol.first << " " << sol.second << "\n";

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
