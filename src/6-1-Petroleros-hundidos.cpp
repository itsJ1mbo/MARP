/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
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
class Manchas {
public:
    Manchas(const std::vector<string>& m) : F(m.size()), C(m[0].size()), conj(F * C), M(m)
    {
	    for (int i = 0; i < m.size(); ++i)
	    {
		    for (int j = 0; j < m[i].size(); ++j)
		    {
			    if (m[i][j] == '#')
			    {
                    creaMancha(i, j);
			    }
		    }
	    }
    }

    void sig(int i, int j)
    {
        M[i][j] = '#';
        creaMancha(i, j);
    }

    int mayor() const
    {
        return max;
    }

private:
    int F, C, max = 0;
    ConjuntosDisjuntos conj;
    std::vector<string> M;
    const vector<pair<int, int>> dirs = { {1,0}, {1, 1}, { 0,1 }, {-1 , 1}, { -1,0 }, {-1 , -1}, { 0,-1 }, {1, -1} };

    bool correcta(int i, int j) const {
        return 0 <= i && i < F && 0 <= j && j < C;
    }

    void creaMancha(int i, int j)
    {
        for (auto d : dirs)
        {
            int ni = i + d.first, nj = j + d.second;
            if (correcta(ni, nj) && M[ni][nj] == '#')
            {
                conj.unir(ni * C + nj, i * C + j);
            }
        }
        max = std::max(max, conj.cardinal(i * C + j));
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int F, C;
    std::cin >> F >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<string> mapa(F);
    for (int i = 0; i < F; i++)
    {
        string col;
        std::cin >> col;
        mapa[i] = col;
    }

    int N;
    std::cin >> N;

    std::vector<pair<int, int>> cont(N);
    for (int i = 0; i < N; ++i)
    {
        int p1, p2;
        std::cin >> p1 >> p2;
        cont[i] = { p1, p2 };
    }

    Manchas m(mapa);

    // escribir la solución
    std::cout << m.mayor();
    for (int i = 0; i < N; ++i)
    {
        std::cout << " ";
        m.sig(cont[i].first-1, cont[i].second-1);
        std::cout << m.mayor();
    }
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
