/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"
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
class ARM_Kruskal 
{
private:
    std::vector<Arista<Valor>> _ARM;
    std::vector<bool> visit;
    Valor coste;
    int aero;

public:
    Valor costeARM() const {
        return coste;
    }

    int puertos()
    {
        return aero;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g, int c) : visit(g.V(), false), coste(0), aero(0) 
	{
	    PriorityQueue<Arista<Valor>> pq(g.aristas());
	    ConjuntosDisjuntos cjtos(g.V());
	    while (!pq.empty()) {
	    	auto a = pq.top(); pq.pop();
	    	int v = a.uno(), w = a.otro(v);
			visit[v] = true; visit[w] = true;
	    	if (!cjtos.unidos(v, w) && c > a.valor()) {
	    		cjtos.unir(v, w);
	    		_ARM.push_back(a); coste += a.valor();
	    		if (_ARM.size() == g.V() - 1) break;
	    	}
	    }

        aero += cjtos.num_cjtos();
		coste += aero * c;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A, C;
    std::cin >> V >> A >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> mapa(V);
    for (int i = 0; i < A; i++)
    {
        int v1, v2, valor;
        std::cin >> v1 >> v2 >> valor;
        mapa.ponArista({ v1 - 1, v2 - 1, valor });
    }

    ARM_Kruskal<int> arm(mapa, C);
    std::cout << arm.costeARM() << " " << arm.puertos() << "\n";

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
