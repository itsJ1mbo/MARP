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
class Tareas {
public:
    Tareas(const Digrafo& g)
        : visit(g.V(), false), apilado(g.V(), false), _hayCiclo(false)
	{
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }

    bool hayCiclo() const { return _hayCiclo; }

    // devuelve la ordenación topológica
    std::deque<int> const& orden() const {
        return _orden;
    }

private:
    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    bool _hayCiclo;

    std::deque<int> _orden; // ordenación topológica

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (_hayCiclo) // si hemos encontrado un ciclo terminamos
                return;
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                // se recupera retrocediendo
                _hayCiclo = true;
            }
        }
        apilado[v] = false;
        _orden.push_front(v);
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

    Tareas t(g);

    // escribir la solución
    if (t.hayCiclo())
        std::cout << "Imposible\n";
    else
    {
        std::deque<int> o = t.orden();
	    while (!o.empty())
	    {
            std::cout << o.front() + 1 << " ";
            o.pop_front();
	    }
        std::cout << "\n";
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
