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
int vacas_rec(string const& patitos, int i, int j, Matriz<int>& patin) {
    int& res = patin[i][j];
    if (res == -1) {
        if (i > j || i == j) res = 0;
        else if (patitos[i] == patitos[j])
            res = vacas_rec(patitos, i + 1, j - 1, patin);
        else
            res = min(vacas_rec(patitos, i + 1, j, patin) + 1,
                vacas_rec(patitos, i, j - 1, patin) + 1);
    }
    return res;
}

void reconstruir(string const& patitos, Matriz<int> const& patin,
    int i, int j, string& sol) {
    if (i > j) return;
    if (i == j) sol.push_back(patitos[i]);
    else if (patitos[i] == patitos[j]) {
        sol.push_back(patitos[i]);
        reconstruir(patitos, patin, i + 1, j - 1, sol);
        sol.push_back(patitos[j]);
    }
    else if (patin[i][j] == patin[i + 1][j] + 1)
    {
        sol.push_back(patitos[i]);
	    reconstruir(patitos, patin, i + 1, j, sol);
        sol.push_back(patitos[i]);
    }
    else
    {
        sol.push_back(patitos[j]);
	    reconstruir(patitos, patin, i, j - 1, sol);
        sol.push_back(patitos[j]);
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    string p;
    std::cin >> p;
    int n = p.length();

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> patindromo(n, n, -1);

    cout << vacas_rec(p, 0, n - 1, patindromo) << ' ';

    string sol;
    reconstruir(p, patindromo, 0, n - 1, sol);
    cout << sol << '\n';

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
