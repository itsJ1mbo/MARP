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
struct Solucion {
    int64_t formas = 0;
    int64_t min_cuerdas = std::numeric_limits<int64_t>::max();
    int64_t min_coste = std::numeric_limits<int64_t>::max();
};

Solucion resolver(const std::vector<std::pair<int, int>>& cordeles, int L)
{
    int n = cordeles.size();
    vector<Solucion> dp(L + 1);

    dp[0].formas = 1;
    dp[0].min_cuerdas = 0;
    dp[0].min_coste = 0;

    // Recorremos cada cordel disponible (Mochila 0/1)
    for (int i = 0; i < n; ++i) 
    {
        int64_t longitud = cordeles[i].first;
        int64_t coste = cordeles[i].second;

        // Iterar de atras hacia adelante para no usar el mismo cordel mas de una vez
        for (int j = L; j >= longitud; --j) 
        {
            // Si es posible alcanzar la longitud previa (j - longitud)
            if (dp[j - longitud].formas > 0)
            {
                dp[j].formas += dp[j - longitud].formas;
                dp[j].min_cuerdas = min(dp[j].min_cuerdas, dp[j - longitud].min_cuerdas + 1);
                dp[j].min_coste = min(dp[j].min_coste, dp[j - longitud].min_coste + coste);
            }
        }
    }

    return dp[L];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, L;
    std::cin >> N >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<std::pair<int, int>> cordeles(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> cordeles[i].first >> cordeles[i].second;
    }

	Solucion sol = resolver(cordeles, L);
    if (sol.formas == 0) {
        cout << "NO\n";
    }
    else {
        cout << "SI " << sol.formas << " " << sol.min_cuerdas << " " << sol.min_coste << "\n";
    }

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
