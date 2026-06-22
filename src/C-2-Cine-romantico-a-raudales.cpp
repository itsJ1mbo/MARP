/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
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
    int inicio;  
    int fin;     
    int duracion; 
};

int autopista_rec(const std::vector<Restaurante>& rest, int i, vector<int>& dp) 
{
    if (i < 0) return 0;
    if (dp[i] == -1)
    {
        if (i == 0) dp[i] = rest[i].duracion;
        else
        {
            auto it = upper_bound(rest.begin(), rest.begin() + i, rest[i].inicio,
                [](int val, Restaurante const& p) {
                    return val < p.fin;
                });
            int p = it - rest.begin() - 1;

        	dp[i] = max(autopista_rec(rest, i - 1, dp), rest[i].duracion + autopista_rec(rest, p, dp));
        }
    }

    return dp[i];
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;

    if (N == 0)  // fin de la entrada
        return false;

    std::vector<Restaurante> pelis(N);
    for (int i = 0; i < N; ++i)
    {
        int dia, horas, minutos, duracion;
        char dos_puntos;

        std::cin >> dia >> horas >> dos_puntos >> minutos >> duracion;

        int inicio_abs = (dia * 24 * 60) + (horas * 60) + minutos;

        int fin_abs = inicio_abs + duracion + 10;

        pelis[i] = { inicio_abs, fin_abs, duracion };
    }

    std::sort(pelis.begin(), pelis.end(), [](Restaurante const& a, Restaurante const& b) {
        return a.fin < b.fin;
        });

    std::vector<int> dp(N, -1);
    std::cout << autopista_rec(pelis, N - 1, dp) << "\n";

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
