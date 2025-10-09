#include <bits/stdc++.h>
using namespace std;

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    const int INF = 1e9;
    vector<vector<int>> dist(n, vector<int>(n, INF));

    // Initialize distances
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        dist[u][v] = w;
        dist[v][u] = w; // bidirectional
    }

    // Floyd-Warshall: All-pairs shortest paths
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int resultCity = -1, minCount = n+1;

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] <= distanceThreshold)
                count++;
        }
        if (count <= minCount) { // choose greatest city number in tie
            minCount = count;
            resultCity = i;
        }
    }

    return resultCity;
}

int main() {
    int n = 4;
    vector<vector<int>> edges = {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    int distanceThreshold = 4;

    int city = findTheCity(n, edges, distanceThreshold);
    cout << "City with smallest number of neighbors: " << city << "\n"; // Output: 3
}
