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
int resolver(std::vector<std::pair<int, int>>& trabajos, int C, int F)
{
    std::sort(trabajos.begin(), trabajos.end());

    int count = 0;
    int i = 0;
    int actual_C = C;

    while (actual_C < F && i < trabajos.size())
    {
        int max_fin = actual_C;
        bool encontrado = false;

        while (i < trabajos.size() && trabajos[i].first <= actual_C) {
            if (trabajos[i].second > max_fin) {
                max_fin = trabajos[i].second;
                encontrado = true;
            }
            i++;
        }

        if (!encontrado) {
            break;
        }

        actual_C = max_fin;
        count++;
    }

    if (actual_C >= F) {
        return count;
    }
    
    return 0;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int C, F, N;
    std::cin >> C >> F >> N;

    if (C == 0 && F == 0 && N == 0)  // fin de la entrada
        return false;

    std::vector<std::pair<int, int>> trabajos(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> trabajos[i].first >> trabajos[i].second;
    }

    int sol = resolver(trabajos, C, F);
    if (sol != 0)
    {
        std::cout << sol << "\n";
    }
    else
    {
		std::cout << "Imposible\n";
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
