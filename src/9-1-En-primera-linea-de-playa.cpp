/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
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
int resolver(std::vector<std::pair<int, int>>& edificios)
{
	std::vector<int> puentes(edificios.size(), 0);
    int np = 1;

	std::sort(edificios.begin(), edificios.end());

    puentes[0] = edificios[0].second - 1;
    for (int i = 1; i < edificios.size(); i++)
    {
        if (puentes[i - 1] == 0 || (puentes[i - 1] != 0 && edificios[i].first > puentes[i - 1]))
        {
            puentes[i] = edificios[i].second - 1;
            np++;
        }
		else if (edificios[i].second < puentes[i - 1]) puentes[i - 1] = puentes[i] = edificios[i].second - 1;
        else puentes[i] = puentes[i - 1];
    }

    return np;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (N == 0)  // fin de la entrada
        return false;

    std::vector<std::pair<int, int>> edificios(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> edificios[i].first >> edificios[i].second;
    }

	int sol = resolver(edificios);
    std::cout << sol << "\n";

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
