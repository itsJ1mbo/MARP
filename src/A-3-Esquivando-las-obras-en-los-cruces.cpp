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
int resolver_rec(const std::vector<string>& mapa, Matriz<int>& formas, int i, int j)
{
    if (i < 0 || j < 0) return 0;

    // calcular la matriz sobre el propio vector
	if (formas[i][j] == -1)
	{
		if (i == 0 && j == 0) formas[i][j] = 1;
		else if (mapa[i][j] == 'X') formas[i][j] = 0;
		else
		{
			formas[i][j] = resolver_rec(mapa, formas, i - 1, j) + resolver_rec(mapa, formas, i, j - 1);
		}
	}

    return formas[i][j];
}

int resolver(const std::vector<string>& mapa)
{
    vector<int> formas(mapa[0].size(), 0);
    formas[0] = 1;
	for (int i = 0; i < mapa.size(); i++)
    {
        if (mapa[i][0] == 'X') {
            formas[0] = 0;
        }
	    for (int j = 1; j < formas.size(); j++)
	    {
			if (mapa[i][j] == 'X') formas[j] = 0;
			else formas[j] = formas[j] + formas[j - 1];
	    }
    }

    return formas.back();
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M;
    std::cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<string> mapa(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> mapa[i];
    }

    //Matriz<int> formas(mapa.size(), mapa[0].size(), -1);
	std::cout << resolver(mapa) << "\n";

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
