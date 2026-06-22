/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
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
struct Restaurante {
    int pos;
    int beneficio;
};

int autopista_rec(const std::vector<Restaurante>& rest, int i, vector<int>& dp, int D)
{
    if (i < 0) return 0;
    if (dp[i] == -1)
    {
        if (i == 0) dp[i] = rest[i].beneficio;
        else
        {
            auto it = upper_bound(rest.begin(), rest.begin() + i, rest[i].pos,
                [D](int val, Restaurante const& p) {
                    return val - D < p.pos;
                });
            int p = it - rest.begin() - 1;

            dp[i] = max(autopista_rec(rest, i - 1, dp, D), rest[i].beneficio + autopista_rec(rest, p, dp, D));
        }
    }

    return dp[i];
}

int autopista(vector<Restaurante> const& objetos, int D, vector<bool>& sol) {
    int n = objetos.size();
    vector<int> dp(n, -1);
    int valor = autopista_rec(objetos, n - 1, dp, D);
    // cálculo de los objetos
    int i = n - 1;
    sol = vector<bool>(n, false);
    while (i > 0) 
    {
        auto it = upper_bound(objetos.begin(), objetos.begin() + i, objetos[i].pos,
            [D](int val, Restaurante const& p) {
                return val - D < p.pos;
            });
        int p = it - objetos.begin() - 1;

        int con_i = objetos[i].beneficio + (p >= 0 ? dp[p] : 0);
        if (dp[i] == con_i) {
            sol[i] = true;
            i = p;
        }
        else --i;
    }

    if (i == 0 && dp[0] > 0) {
        sol[0] = true;
    }

    return valor;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int R, D;
    std::cin >> R >> D;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<Restaurante> res(R);
    for (int i = 0; i < R; ++i) {
        std::cin >> res[i].pos ;
    }
    for (int i = 0; i < R; ++i) {
        std::cin >> res[i].beneficio;
    }

    vector<bool> sol;
    std::cout << autopista(res, D, sol) << "\n";
    for (int i = 0; i < R; i++) {
        if (sol[i]) std::cout << res[i].pos << " ";
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
