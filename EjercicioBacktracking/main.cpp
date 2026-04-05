#include <iostream>
#include <vector>
#include <chrono> // libreria agregada para medir el tiempo
using namespace std;

int n, k;
vector<vector<int>> matriz_ady;
vector<int> color;
int totalSoluciones = 0;
bool primeraGuardada = false;
vector<int> primeraSolucion;

bool EsSeguro(int v,int c){
    for (int u=0; u < n; u++) {
        if (matriz_ady[v][u] == 1 && color[u] == c)
            return false; // un vecino ya tiene ese color, no es seguro :(
    }
    return true; //ningun vecino tiene ese color, es seguro :)
}

void bt(int v) {
    // si v es igual n, ya coloreamos todos los vertices, es una solucion valida
    if (v == n) {
        totalSoluciones++;
        if (!primeraGuardada) {
            primeraSolucion = color;
            primeraGuardada = true;
        }
        return;
    }

    for (int c = 1; c <= k; c++) {
        if (EsSeguro(v, c)) {
            color[v] = c;       // Se prueba este color en el vertice v
            bt(v + 1);          // Aqui usamos recursion: pasar al siguiente vertice
            color[v] = 0;       // aqui se hace el backtrack, se quita el color para probar el siguiente
        }
    }
}
void fuerza_bruta() {
    int total_fb = 0;
    vector<int> asignacion(n, 1);

    // generar todas las combinaciones posibles
    while (true) {
        // verificar si la asignacion actual es valida
        bool valida = true;
        for (int v = 0; v < n && valida; v++) {
            for (int u = v + 1; u < n && valida; u++) {
                if (matriz_ady[v][u] == 1 && asignacion[v] == asignacion[u])
                    valida = false;
            }
        }
        if (valida) total_fb++;

        // pasar a la siguiente combinacion
        int pos = n - 1;
        while (pos >= 0 && asignacion[pos] == k) {
            asignacion[pos] = 1;
            pos--;
        }
        if (pos < 0) break;
        asignacion[pos]++;
    }

    cout << "Fuerza Bruta confirma: " << total_fb << "\n";
}

int main() {
    // leer n y k
    cout << "Ingrese n y k: ";
    cin >> n >> k;

    // leer matriz de adyacencia
    matriz_ady.assign(n, vector<int>(n));
    cout << "Ingrese la matriz de adyacencia:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> matriz_ady[i][j];

    color.assign(n, 0);

    // medir backtracking
    auto inicio_bt = chrono::high_resolution_clock::now();
    bt(0);
    auto fin_bt = chrono::high_resolution_clock::now();

    // imprimir resultados
    if (totalSoluciones == 0) {
        cout << "No existe una " << k << "-coloracion valida\n";
    } else {
        cout << "Total de " << k << "-coloraciones: " << totalSoluciones << "\n";
        cout << "Primera solucion:\n";
        for (int v = 0; v < n; v++)
            cout << "color[" << v << "] = " << primeraSolucion[v] << "\n";
    }

    // medir fuerza bruta
    auto inicio_fb = chrono::high_resolution_clock::now();
    fuerza_bruta();
    auto fin_fb = chrono::high_resolution_clock::now();

    cout << "Tiempo BT: "
         << chrono::duration_cast<chrono::microseconds>(fin_bt - inicio_bt).count()
         << " microsegundos\n";
    cout << "Tiempo FB: "
         << chrono::duration_cast<chrono::microseconds>(fin_fb - inicio_fb).count()
         << " microsegundos\n";

    return 0;
}
// Código desarrollado con apoyo de Claude (Anthropic, 2025).