/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
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
class Camiones {
public:
    Camiones(const GrafoValorado<int>& g, int o, int d, int v) : visit(g.V(), false), des(d)
    {
        dfs(g, o, v);
    }

    bool alcanzable()
    {
        return visit[des];
    }

private:
    std::vector<bool> visit;
    int des;

    void dfs(GrafoValorado<int> const& G, int v, int umbral) {
        visit[v] = true;
        for (auto a : G.ady(v)) {
            if (a.valor() >= umbral) {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(G, w, umbral);
            }
        }
    }
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

    int C;
    std::cin >> C;
    for (int i = 0; i < C; ++i)
    {
        int o, d, v;
        std::cin >> o >> d >> v;
        Camiones c(mapa, o - 1, d - 1, v);
        if (c.alcanzable())
            std::cout << "SI\n";
        else
            std::cout << "NO\n";
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
