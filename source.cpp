#include <iomanip> 
#include <vector> 
#include <iostream>
using namespace std;


vector<double> gauss(vector<vector<double>> A, vector<double> b) {
    int n = (int)A.size();

    for (int k = 0; k < n; ++k) {
        for (int i = k+1; i < n; ++i) {
            double fator = A[i][k] / A[k][k];
            for (int j = k; j < n; ++j) {
                A[i][j] -= fator * A[k][j];
            }
            b[i] -= fator * b[k];
        }
    }

    vector<double> x(n, 0.0);
    for (int i = n-1; i >= 0; --i) {
        double s = b[i];
        for (int j = i+1; j < n; ++j) {
            s -= A[i][j] * x[j];
        }
        x[i] = s / A[i][i];
    }
    return x;
}

void criaMatriz(vector<vector<double>> &A, vector<double> &b, int n) {
    double diagonalPrincipal = (n - 1.0) / n;        
    double lado  = -(n - 1.0) / (2.0 * n); 

    // preenche a matriz A
    for (int i = 0; i < n; i++) {
        A[i][i] = diagonalPrincipal;               
        if (i > 0)     A[i][i-1] = lado; 
        if (i < n-1)   A[i][i+1] = lado; 
    }

    // define vetor b
    int central = n / 2;
    b[central] = 1.0;

    // imprime a matriz:

    /*
    cout << fixed << setprecision(4);
    cout << "Matriz A e vetor b:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(7) << A[i][j] << " ";
        }
        cout << "| " << b[i] << "\n";
    }
    */
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

    criaMatriz(A, b, n);

    vector<double> x = gauss(A, b);

    cout << "\nSolucao x:\n";
    cout << fixed << setprecision(6);
    double soma = 0;
    for (int i = 0; i < n; ++i) {
        //cout << "x[" << i << "] = " << x[i] << "\n";
        soma += x[i];
    }

    cout << "Total: " << soma << endl;
    return 0;
}
