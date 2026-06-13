/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <ConjuntosDisjuntos.h>
#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
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
class Puentes
{
public:
    Puentes(GrafoValorado<int> const& g) : cjtos(g.V()), coste(0)
	{
        PriorityQueue<Arista<int>> pq(g.aristas());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); coste += a.valor();
                if (_ARM.size() == g.V() - 1) break;
            }
        }
    }

    int costeARM() const {
        return coste;
    }

	std::vector<Arista<int>> const& ARM() const {
        return _ARM;
    }

    bool haySolucion()
    {
        return cjtos.num_cjtos() == 1;
    }

private:
    std::vector<Arista<int>> _ARM;
    ConjuntosDisjuntos cjtos;
    int coste;
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> mapa(V);
    for (int i = 0; i < A; i++)
    {
        int v1, v2, valor;
        std::cin >> v1 >> v2 >> valor;
        mapa.ponArista({ v1 - 1, v2 - 1, valor });
    }

    Puentes p(mapa);
    if (p.haySolucion())
        std::cout << p.costeARM() << "\n";
    else
        std::cout << "No hay puentes suficientes\n";

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
