/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
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
struct Festival { int profundidad; double precio; };

double mochila_rec(vector<Festival> const& obj, int i, int j, Matriz<double>& mochila) 
{
    if (mochila[i][j] != -1) // subproblema ya resuelto
        return mochila[i][j];
    if (i == 0 || j == 0) mochila[i][j] = 0;
    else if (obj[i - 1].profundidad + 2 * obj[i - 1].profundidad > j)
        mochila[i][j] = mochila_rec(obj, i - 1, j, mochila);
    else
        mochila[i][j] = max(mochila_rec(obj, i - 1, j, mochila),
            mochila_rec(obj, i - 1, j - (obj[i - 1].profundidad + 2 * obj[i - 1].profundidad), mochila) + obj[i - 1].precio);
    return mochila[i][j];
}

double mochila(vector<Festival> const& objetos, int M, vector<bool>& sol, int& a) 
{
    int n = objetos.size();
    Matriz<double> mochila(n + 1, M + 1, -1);
    double valor = mochila_rec(objetos, n, M, mochila);
    // cálculo de los objetos
    int i = n, j = M;
    sol = vector<bool>(n, false);
    while (i > 0 && j > 0) {
        if (mochila[i][j] != mochila[i - 1][j]) {
            sol[i - 1] = true; j = j - (objetos[i - 1].profundidad + 2 * objetos[i - 1].profundidad); a++;
        }
        --i;
    }
    return valor;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int T, N;
    std::cin >> T >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<Festival> cofres(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> cofres[i].profundidad >> cofres[i].precio;
    }

    int n = 0;
    std::vector<bool> sol(N);
	double valor = mochila(cofres, T, sol, n);
	std::cout << valor << "\n" << n << "\n";
    for (int i = 0; i < N; i++)
    {
        if (sol[i])
            std::cout << cofres[i].profundidad << " " << cofres[i].precio << "\n";
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
