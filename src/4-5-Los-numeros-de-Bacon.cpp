/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>

#include "../header/Grafo.h"

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
struct Pelicula
{
    string nombre;
	vector<string> actores;
};

class Bacon
{
public:
    Bacon(const Grafo& g, int o) :
		visit(g.V(), false),
		dist(g.V(), -1),
		s(o)
    {
        bfs(g);
    }

    int getBaconNumber(int v) const
    {
        if (dist[v] == -1)
            return -1; // INF
        return dist[v] / 2;
    }

private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> dist; // dist[v] = aristas en el camino s-v más corto
    int s;

    void bfs(const Grafo& g) {
        queue<int> q;
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
    int N;
	std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    std::unordered_map<string, int> nodes;
    int nNodes = 0;

	std::vector<Pelicula> peliculas(N);
	for (int i = 0; i < N; ++i)
	{
		std::cin >> peliculas[i].nombre;
        int A;
        std::cin >> A;

        for (int j = 0; j < A; ++j)
        {
            string actor;
            std::cin >> actor;
            nodes[actor] = nNodes++;
            peliculas[i].actores.push_back(actor);
        }

        nodes[peliculas[i].nombre] = nNodes++;
	}

    Grafo g(nNodes);
    for (const auto& i : peliculas)
    {
        for (int j = 0; j < i.actores.size(); ++j)
        {
            g.ponArista(nodes[i.nombre], nodes[i.actores[j]]);
        }
    }

    int M;
    std::cin >> M;

    std::vector<string> actores(M);
    for (int i = 0; i < M; ++i)
    {
        string actor;
        std::cin >> actor;
        actores[i] = actor;
    }

    // resolver el caso posiblemente llamando a otras funciones
    auto it = nodes.find("KevinBacon");
    if (it == nodes.end()) 
    {
        for (int i = 0; i < M; ++i) {
            cout << actores[i] << " INF\n";
        }
        cout << "---\n";
        return true;
    }

    Bacon l(g, it->second);

    // escribir la solución
    for (int i = 0; i < M; ++i) {
        int bn = l.getBaconNumber(nodes[actores[i]]);
        if (bn == -1)
            std::cout << actores[i] << " INF\n";
        else
            std::cout << actores[i] << " " << bn << "\n";
    }
    std::cout << "---\n";

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
