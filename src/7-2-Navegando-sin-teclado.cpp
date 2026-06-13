/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <deque>
#include <limits>
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
    Dijkstra(DigrafoValorado<Valor> const& g, int orig, const std::vector<int>& l) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = l[origen];
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a, l[a.hasta()]);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    std::deque<AristaDirigida<Valor>> camino(int v) const {
        std::deque<AristaDirigida<Valor>> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a, int load) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor() + load) {
            dist[w] = dist[v] + a.valor() + load; ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V;
    std::cin >> V;

    if (V == 0)  // fin de la entrada
        return false;

    std::vector<int> loads(V);
	for (int i = 0; i < V; i++)
	{
		std::cin >> loads[i];
	}

    int A;
    std::cin >> A;

    DigrafoValorado<int> mapa(V);
    for (int i = 0; i < A; i++)
    {
        int v1, v2, valor;
        std::cin >> v1 >> v2 >> valor;
        mapa.ponArista({ v1 - 1, v2 - 1, valor });
    }
;
    Dijkstra<int> p(mapa, 0, loads);
    if (p.hayCamino(V - 1))
    {
        std::cout << p.distancia(V - 1);
    }
    else std::cout << "IMPOSIBLE";
    std::cout << "\n";

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
