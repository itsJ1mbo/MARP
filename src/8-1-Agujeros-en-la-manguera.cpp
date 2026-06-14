/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
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
class Manguera {
public:
    Manguera(const std::vector<int>& parches, int L) : num(1), l(L)
    {
	    for (int i = 0; i < parches.size() - 1; i++)
	    {
			int pos = parches[i];
            if (pos + l >= parches[i + 1])
            {
				l -= parches[i + 1] - pos;
            }
            else
            {
                l = L;
	            num++;
            }
	    }
    }

    int parches() const { return num; }

private:
    int num, l;
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, L;
    std::cin >> N >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> parches(N);
    for (int i = 0; i < N; i++)
    {
		std::cin >> parches[i];
    }

    Manguera m(parches, L);
    std::cout << m.parches() << "\n";

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
