/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <algorithm>
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
class Invaden {
public:
    Invaden(std::vector<int>& enemigos, std::vector<int>& aliados) : ciu(0)
    {
	    std::sort(enemigos.begin(), enemigos.end());
        std::sort(aliados.begin(), aliados.end());

        int i = 0;
        int j = 0;

        while (i < enemigos.size() && j < aliados.size()) {
            if (aliados[j] >= enemigos[i]) {
                ciu++;
                i++; 
                j++; 
            }
            else {
                j++;
            }
        }
    }

    int ciudades() const { return ciu; }

private:
    int ciu;
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> enemigos(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> enemigos[i];
    }
    std::vector<int> aliados(N);
	for (int i = 0; i < N; i++)
	{
		std::cin >> aliados[i];
	}

	Invaden i(enemigos, aliados);
	std::cout << i.ciudades() << "\n";

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
