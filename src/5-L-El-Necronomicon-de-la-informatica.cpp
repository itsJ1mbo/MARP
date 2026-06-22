/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include "Digrafo.h"
#include <unordered_map>

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
using Camino = std::deque<int>;

class CicloDirigido 
{
public:
    CicloDirigido(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false), salto(false)
	{
        dfs(g, 0);
    }
    
    bool hayCiclo()
    {
        return salto;
    }

    bool puedeLlegar(int v)
    {
        return visit[v];
    }

private:
    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    bool salto;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                // se recupera retrocediendo
                salto = true;
            }
        }
        apilado[v] = false;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V;
    std::cin >> V;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(V + 1);
    for (int i = 0; i < V; ++i) {
        char tipo;
        cin >> tipo;
        if (tipo == 'A') {
            g.ponArista(i, i + 1);
        }
        else if (tipo == 'J') {
            int destino;
            cin >> destino;
            g.ponArista(i, destino - 1);
        }
        else if (tipo == 'C') {
            int destino;
            cin >> destino;
            g.ponArista(i, destino - 1); // Opción de saltar
            g.ponArista(i, i + 1);       // Opción de continuar en secuencia
        }
    }

    CicloDirigido l(g);
    if (!l.puedeLlegar(V))
		std::cout << "NUNCA\n";
	else if (l.hayCiclo())
		std::cout << "A VECES\n";
	else
		std::cout << "SIEMPRE\n";

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
