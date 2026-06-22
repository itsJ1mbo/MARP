/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <limits>
#include "deque"
#include "DigrafoValorado.h"
#include "IndexPQ.h"
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
template <typename Valor>
class Dijkstra {
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> mapa(V);
    for (int i = 0; i < A; i++)
    {
        int v1, v2, valor;
        std::cin >> v1 >> v2 >> valor;
        mapa.ponArista({ v1 - 1, v2 - 1, valor });
    }

    int O, P, coste = 0;
	std::cin >> O >> P;
    Dijkstra<int> d(mapa, O - 1);
    Dijkstra<int> inv(mapa.inverso(), O - 1);

    bool posible = true;
    for (int i = 0; i < P; i++)
    {
        int pqt;
		cin >> pqt;

        if (d.hayCamino(pqt - 1) && inv.hayCamino(pqt - 1))
        {
			coste += d.distancia(pqt - 1) + inv.distancia(pqt - 1);
        }
		else
		{
			posible = false;
		}
    }

    if (posible)
        std::cout << coste << "\n";
    else
        std::cout << "Imposible\n";

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
