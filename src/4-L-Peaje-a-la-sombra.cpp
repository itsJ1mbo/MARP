/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include "Grafo.h"

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
class Luces
{
public:
	Luces(const Grafo& g, int C1, int C2, int T) : visit(g.V(), false), 
													distC1(g.V(), -1), distC2(g.V(), -1), distT(g.V(), -1), 
													s(C1)
	{
        bfs(g, distC1);
        s = C2;
        visit.assign(g.V(), false);
        bfs(g, distC2);
        s = T;
        visit.assign(g.V(), false);
        bfs(g, distT);

        for (int i = 0; i < g.V(); ++i) {
            suma = min(suma, distC1[i] + distC2[i] + distT[i]);
        }
    }

    int coste() const {
        return suma;
    }

private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> distC1; // dist[v] = aristas en el camino s-v más corto
    std::vector<int> distC2; // dist[v] = aristas en el camino s-v más corto
    std::vector<int> distT; // dist[v] = aristas en el camino s-v más corto
    int s, suma = numeric_limits<int>::max();

    void bfs(Grafo const& g, std::vector<int>& dist) {
        std::queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A, C1, C2, T;
    std::cin >> V >> A >> C1 >> C2 >> T;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(V);
    for (int i = 0; i < A; ++i) {
        int u, v;
        std::cin >> u >> v;
        g.ponArista(u - 1, v - 1);
    }

	Luces l(g, C1 - 1, C2 - 1, T - 1);
	std::cout << l.coste() << "\n";

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
