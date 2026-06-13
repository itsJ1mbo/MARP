/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
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
class Libre
{
public:
    Libre(const Grafo& g) : visit(g.V(), false), ant(g.V())
    {
		dfs(g, 0);
    }

    bool ciclo() const
    {
        return _ciclo;
    }

    bool conexo()
    {
	    for (int i = 0; i < visit.size(); ++i)
	    {
            if (!visit[i]) return false;
	    }

        return true;
    }

private:
    std::vector<bool> visit;
    std::vector<int> ant;

    bool _ciclo = false;

    void dfs(Grafo const& G, int v)
	{
        visit[v] = true;
        for (int w : G.ady(v)) 
        {
            if (!visit[w]) 
            {
                ant[w] = v;
            	dfs(G, w);
            }
            else if (w != ant[v])
            {
                _ciclo = true;
            }
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int A, V;
    std::cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(V);

    for (int i = 0; i < A; i++)
    {
        int v1, v2;
		std::cin >> v1 >> v2;
        g.ponArista(v1, v2);
    }
    
    // resolver el caso posiblemente llamando a otras funciones
	Libre l(g);
    if (!l.ciclo() && l.conexo()) std::cout << "SI\n";
	else std::cout << "NO\n";

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
