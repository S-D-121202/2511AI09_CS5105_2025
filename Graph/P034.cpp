#include <bits/stdc++.h>
using namespace std;

void floydWarshall(vector<vector<int>>& Matrix) {
    int n = Matrix.size();
    const int INF = 1e9;

    // Step 1: Replace -1 with INF
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Matrix[i][j] == -1) Matrix[i][j] = INF;
            if (i == j) Matrix[i][j] = 0;
        }
    }

    // Step 2: Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (Matrix[i][k] < INF && Matrix[k][j] < INF) {
                    Matrix[i][j] = min(Matrix[i][j], Matrix[i][k] + Matrix[k][j]);
                }
            }
        }
    }

    // Step 3: Replace INF back with -1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (Matrix[i][j] == INF) Matrix[i][j] = -1;
        }
    }
}

int main() {
    vector<vector<int>> Matrix = {
        {0, 3, -1, 7},
        {8, 0, 2, -1},
        {5, -1, 0, 1},
        {2, -1, -1, 0}
    };

    floydWarshall(Matrix);

    cout << "All pairs shortest distances:\n";
    for (auto &row : Matrix) {
        for (int d : row) cout << d << " ";
        cout << "\n";
    }
}
