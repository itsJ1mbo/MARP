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
    Dijkstra(DigrafoValorado<Valor> const& g, int orig, int d) : origen(orig), des(d),
        dist(g.V(), INF), pq(g.V()), num_caminos(g.V(), 0) {

        dist[origen] = 0;
        num_caminos[origen] = 1;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    int caminos() const { return num_caminos[des]; }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen, des;
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;
    std::vector<int> num_caminos;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[v] + a.valor() < dist[w]) {
            dist[w] = dist[v] + a.valor();
            num_caminos[w] = num_caminos[v];
            pq.update(w, dist[w]);
        }
        else if (dist[v] + a.valor() == dist[w]) {
            num_caminos[w] += num_caminos[v];
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
        mapa.ponArista({ v2 - 1, v1 - 1, valor });
    }
    
    Dijkstra<int> p(mapa, 0, V - 1);
	std::cout << p.caminos();
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
