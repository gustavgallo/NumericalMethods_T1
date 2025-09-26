#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void criaMatriz(vector<vector<double>> &A, vector<double> &b, double n){

    double diagonalPrincipal = (n - 1.0) / n;        
    double lado  = -(n - 1.0) / (2.0 * n); 

  // preenche a matriz A
    for (int i = 0; i < n; i++) {

        A[i][i] = diagonalPrincipal;               
        if (i > 0)     A[i][i-1] = lado; 
        if (i < n-1)   A[i][i+1] = lado; 

    }

    int central = n / 2;
    b[central] = 1.0;

    // imprime A e b
    cout << fixed << setprecision(4);
    cout << "Matriz A e vetor b:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(7) << A[i][j] << " ";
        }
        cout << "| " << b[i] << "\n";
    }

}
int main() {
    int n;
    do {
        cout << "Digite o numero de salas (impar): ";
        cin >> n;
        if (n % 2 == 0) {
            cout << "Por favor, digite um numero impar.\n";
        }
    } while (n % 2 == 0);


    vector<vector<double>> A(n, vector<double>(n, 0.0));
    vector<double> b(n, 0.0);

    criaMatriz(A,b,n);

    return 0;
}
