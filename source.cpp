#include <bits/stdc++.h>
using namespace std;

// Função para resolver sistema linear Ax = b por eliminação de Gauss
vector<double> gaussSolve(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        A[i].push_back(b[i]); // junta b na matriz (aumentada)
    }

    // Eliminação
    for (int i = 0; i < n; i++) {
        // pivô
        int pivot = i;
        for (int j = i+1; j < n; j++) {
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        }
        swap(A[i], A[pivot]);

        // normaliza pivô
        double div = A[i][i];
        if (fabs(div) < 1e-12) continue; // só por segurança
        for (int j = i; j <= n; j++) A[i][j] /= div;

        // elimina nas outras linhas
        for (int k = 0; k < n; k++) {
            if (k == i) continue;
            double factor = A[k][i];
            for (int j = i; j <= n; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }

    vector<double> x(n);
    for (int i = 0; i < n; i++) x[i] = A[i][n];
    return x;
}

double populationForN(int n, double arrival_rate=1.0) {
    int N = n;
    double p_stay = 1.0 / n;
    double p_move = (n - 1.0) / (2.0 * n);

    vector<vector<double>> A(N, vector<double>(N, 0.0));
    vector<double> b(N, 1.0);

    for (int i = 0; i < N; i++) {
        A[i][i] = 1.0 - p_stay;

        if (i - 1 >= 0) A[i][i-1] -= p_move; // vizinho esquerdo
        if (i + 1 < N) A[i][i+1] -= p_move; // vizinho direito
    }

    // ---- Imprimir a matriz do sistema linear ----
    cout << "Matriz do sistema (A|b):" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(10) << fixed << setprecision(4) << A[i][j] << " ";
        }
        cout << " | " << setw(10) << fixed << setprecision(4) << b[i] << endl;
    }
    cout << endl;

    // Resolver
    vector<double> E = gaussSolve(A, b);
    int center = (n - 1) / 2;
    double T = E[center];
    return arrival_rate * T;
}

int main() {
    int n;
    do {
        cout << "Digite o numero de salas (impar): ";
        cin >> n;
        if (n % 2 == 0) {
            cout << "Por favor, digite um numero impar." << endl;
        }
    } while (n % 2 == 0);

    double result = populationForN(n);
    cout << "Populacao media para " << n << " salas: "
         << fixed << setprecision(2) << result << endl;

    return 0;
}
