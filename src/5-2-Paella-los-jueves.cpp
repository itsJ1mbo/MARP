/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

#include "Digrafo.h"
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
class Paella {
public:
    Paella(const Digrafo& g, int o, int d)
        : desdeO(g.V(), false), hastaD(g.V(), false), valido(false)
    {
        dfs(g, o, desdeO);
        dfs(g.inverso(), d, hastaD);
        valido = desdeO[d];
    }

    bool posible() const { return valido; }

    int restaurantes() const {
        int n = 0;
        for (int i = 0; i < (int)desdeO.size(); i++)
            if (desdeO[i] && hastaD[i])
                n++;

        return n-2;
    }

private:
    std::vector<bool> desdeO, hastaD;
    bool valido;

    void dfs(const Digrafo& g, int v, std::vector<bool>& visit) {
        visit[v] = true;
        for (int w : g.ady(v))
            if (!visit[w])
                dfs(g, w, visit);
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int A, V;
    std::cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(V);

    for (int i = 0; i < A; i++)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        g.ponArista(v1 - 1, v2 - 1);
    }

    int C;
    std::cin >> C;
    std::vector<pair<int, int>> ruta;
    for (int i = 0; i < C; ++i)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        Paella l(g, v1 - 1, v2 - 1);

        if (l.posible())
            std::cout << l.restaurantes() << "\n";
        else
            std::cout << "IMPOSIBLE\n";
    }
    std::cout << "---\n";

    // escribir la solución

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
