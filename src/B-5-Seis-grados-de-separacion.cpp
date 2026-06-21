/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Matriz.h"
#include "EnterosInf.h"
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
void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<int>& A) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    A = Matriz<int>(V, V, -1);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && G[i][j] != Infinito)
                A[i][j] = i;
        }
    }

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                    A[i][j] = A[k][j];
                }
            }
        }
    }
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    std::cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<EntInf> grafo(V, V, Infinito);
    for (int i = 0; i < V; ++i) {
        grafo[i][i] = 0;
    }

    std::unordered_map<string, int> personas;
    int id_actual = 0;

    for (int i = 0; i < A; ++i)
    {
        string p1, p2;
        cin >> p1 >> p2;

        if (personas.find(p1) == personas.end()) {
            personas[p1] = id_actual++;
        }

        if (personas.find(p2) == personas.end()) {
            personas[p2] = id_actual++;
        }

        int u = personas[p1];
        int v = personas[p2];

        grafo[u][v] = 1;
        grafo[v][u] = 1;
    }

    // Matrices para recoger la respuesta
    Matriz<EntInf> distancias(V, V);
    Matriz<int> caminos(V, V);

    Floyd(grafo, distancias, caminos);

    EntInf max_grado = 0;
    bool desconectada = false;

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (distancias[i][j] == Infinito) 
            {
                desconectada = true;
            }
            else if (max_grado < distancias[i][j]) 
            {
                max_grado = distancias[i][j];
            }
        }
    }

    if (desconectada) {
        cout << "DESCONECTADA\n";
    }
    else {
        cout << max_grado << "\n";
    }

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
