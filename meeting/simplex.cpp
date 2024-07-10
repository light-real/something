#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

const double EPSILON = 1.0e-10;

class Simplex {
private:
    int m, n;
    vector<vector<double>> tableau;
    vector<int> basis;

    void printTableau() {
        cout << "Tableau:" << endl;
        for (const auto& row : tableau) {
            for (double value : row) {
                cout << value << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    void pivot(int row, int col) {
        for (int i = 0; i <= n; ++i) {
            if (i != col) tableau[row][i] /= tableau[row][col];
        }
        tableau[row][col] = 1.0;

        for (int i = 0; i <= m; ++i) {
            if (i != row) {
                double factor = tableau[i][col];
                for (int j = 0; j <= n; ++j) {
                    if (j != col) tableau[i][j] -= factor * tableau[row][j];
                }
                tableau[i][col] = 0.0;
            }
        }

        printTableau();
    }

public:
    Simplex(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c) {
        m = b.size();
        n = c.size();
        tableau.resize(m + 1, vector<double>(n + 1));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                tableau[i][j] = A[i][j];
            }
        }

        for (int i = 0; i < m; ++i) {
            tableau[i][n] = b[i];
        }

        for (int j = 0; j < n; ++j) {
            tableau[m][j] = -c[j];
        }

        basis.resize(m);
        for (int i = 0; i < m; ++i) {
            basis[i] = n + i;
        }

        printTableau();
    }

    double solve() {
        while (true) {
            int pivot_col = -1;
            for (int j = 0; j < n; ++j) {
                if (tableau[m][j] < -EPSILON) {
                    pivot_col = j;
                    break;
                }
            }

            if (pivot_col == -1) break;

            int pivot_row = -1;
            for (int i = 0; i < m; ++i) {
                if (tableau[i][pivot_col] > EPSILON) {
                    if (pivot_row == -1 || tableau[i][n] / tableau[i][pivot_col] < tableau[pivot_row][n] / tableau[pivot_row][pivot_col]) {
                        pivot_row = i;
                    }
                }
            }

            if (pivot_row == -1) throw "Linear program is unbounded";

            pivot(pivot_row, pivot_col);
            basis[pivot_row] = pivot_col;
        }

        vector<double> solution(n);
        for (int i = 0; i < m; ++i) {
            if (basis[i] < n) solution[basis[i]] = tableau[i][n];
        }

        return tableau[m][n];
    }
};


/*
maximize    10x1 + 12x2
subject to  2x1 + x2  <= 20
            x1 + 2x2  <= 20
            x1 - x2   <= 10
            x1, x2 >= 0
*/
int main() {
    vector<vector<double>> A = {
        {2, 1},
        {1, 2},
        {1, -1}
    };
    vector<double> b = {20, 20, 10};
    vector<double> c = {10, 12};

    Simplex simplex(A, b, c);
    try {
        double max_value = simplex.solve();
        cout << "Optimal value: " << max_value << endl;
    } catch (const char *msg) {
        cerr << msg << endl;
    }

    return 0;
}
