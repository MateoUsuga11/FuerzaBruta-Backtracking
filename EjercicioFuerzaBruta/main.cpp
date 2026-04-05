#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Ingrese n: "; //aqui defino el tamaño del vector
    cin >> n;

    vector<int> A(n);
    cout << "Ingrese los " << n << " enteros distintos: ";
    for (int i = 0; i < n; i++)
        cin >> A[i]; //se le asignan valores al vector con los numeros del usuario

    sort(A.begin(), A.end());

    int total_generadas = 0;
    int total_validas = 0;

    do {
        total_generadas += 1;

        bool valida = true;
        for (int i = 0; i <= n - 2; i++) {
            if (A[i] > 2 * A[i + 1]) { //se van revisando por pares, si alguno incumple la condicion, la permutacion es invalida
                valida = false;
                break;
            }
        }

        if (valida) {
            for (int i = 0; i < n; i++)
                cout << A[i] << " "; //si son validas imprimo, salto linea y añado al contador
            cout << "\n";
            total_validas += 1;
        }

    } while (next_permutation(A.begin(), A.end()));

    cout << "total_generadas = " << total_generadas << "\n"; //se imprimen los valores en general y los validos segun la condicion
    cout << "total_validas   = " << total_validas   << "\n";

    return 0;
}
