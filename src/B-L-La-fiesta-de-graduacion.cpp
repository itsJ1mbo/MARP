/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
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
int musica_rec(const vector<string>& lista1, const vector<string>& lista2, int i, int j, Matriz<int>& mus) 
{
    int& res = mus[i][j];
    if (res == -1) {
        if (i == lista1.size() || j == lista2.size())
            res = 0;
    	else if (lista1[i] == lista2[j])
            res = musica_rec(lista1, lista2, i + 1, j + 1, mus) + 1;
        else
            res = max(musica_rec(lista1, lista2, i + 1, j, mus),
                musica_rec(lista1, lista2, i, j + 1, mus));
    }
    return res;
}

void reconstruir(const vector<string>& lista1, const vector<string>& lista2, Matriz<int> const& mus, int i, int j, vector<string>& sol) 
{
    if (i == lista1.size() || j == lista2.size()) return;
    if (lista1[i] == lista2[j]) {
        sol.push_back(lista1[i]);
        reconstruir(lista1, lista2, mus, i + 1, j + 1, sol);
    }
    else if (mus[i][j] == mus[i + 1][j])
        reconstruir(lista1, lista2, mus, i + 1, j, sol);
    else
        reconstruir(lista1, lista2, mus, i, j + 1, sol);
}

bool resuelveCaso() {

    string linea1, linea2;

    // 1. Intentamos leer la primera línea completa. 
    // Si getline devuelve 'false', significa que hemos llegado al final del archivo (EOF).
    if (!std::getline(std::cin, linea1))
        return false;

    // 2. Leemos la segunda línea completa que corresponde al mismo caso.
    std::getline(std::cin, linea2);

    // 3. Procesamos la primera línea para extraer sus canciones
    vector<string> lista_manana;
    stringstream ss1(linea1); // Convertimos el string en un flujo (stream) de lectura
    string cancion;
    while (ss1 >> cancion) {   // Extrae palabra por palabra separando por los espacios
        lista_manana.push_back(cancion);
    }

    // 4. Procesamos la segunda línea para extraer sus canciones
    vector<string> lista_tarde;
    stringstream ss2(linea2);
    while (ss2 >> cancion) {
        lista_tarde.push_back(cancion);
    }

    Matriz<int> musica(lista_manana.size() + 1, lista_tarde.size() + 1, -1);
    musica_rec(lista_manana, lista_tarde, 0, 0, musica);

    vector<string> sol;
    reconstruir(lista_manana, lista_tarde, musica, 0, 0, sol);
    for (auto s : sol)
	{
	    cout << s << " ";
    }
    cout << "\n";

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
